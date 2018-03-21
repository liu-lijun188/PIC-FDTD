//! \file
//! \brief Implementation of Particle class 
//! \author Rahul Kalampattel
//! \date Last updated March 2018

#include "Particle.h"

// Default constructor
Particle::Particle()
{
}


// Initial constructor
Particle::Particle(Parameters *parametersList, Mesh *mesh, int patchID, int cellID, int particleID, int index)
{
	this->particleID = particleID;
	this->cellID = cellID;

	if (parametersList->simulationType == "electron")
	{
		this->basic.q = ELECTRON_CHARGE;
		this->basic.m = ELECTRON_MASS_kg;
	}
	else
	{
		if (parametersList->propellant == "xenon")
		{
			this->basic.q = 0.0;
			this->basic.m = XENON_MASS_kg;
		}
	}

	if (parametersList->particlesPerCell == 1)
	{
		// TODO: Add third component of position, set to zero
		// Place particle in cell at location (xInitial, yInitial)
		position.push_back(mesh->cellsVector.cells[cellID - 1].left * (1 - parametersList->xInitial) +
			mesh->cellsVector.cells[cellID - 1].right * parametersList->xInitial);			// x
		position.push_back(mesh->cellsVector.cells[cellID - 1].top * parametersList->yInitial +
			mesh->cellsVector.cells[cellID - 1].bottom * (1 - parametersList->yInitial));		// y
	}
	else
	{
		// Distribute particles uniformly in cell
		double xratio = (0.5 + static_cast<double>(index % 
			static_cast<int>(sqrt(parametersList->particlesPerCell)))) / 
			sqrt(parametersList->particlesPerCell);
		double yratio = (0.5 + static_cast<double>(floor(index /
			sqrt(parametersList->particlesPerCell)))) / sqrt(parametersList->particlesPerCell);

		position.push_back(mesh->cellsVector.cells[cellID - 1].left * (1 - xratio) +
			mesh->cellsVector.cells[cellID - 1].right * xratio);			// x
		position.push_back(mesh->cellsVector.cells[cellID - 1].top * yratio +
			mesh->cellsVector.cells[cellID - 1].bottom * (1 - yratio));		// y

		// TODO: Method for distributing particles when simulation is axisymmetric,
		// need to ensure same number of particles per unit cell volume, i.e.
		// cells closer to the axis will have different numbers of particles
		// compared to cells at a distance
	}

	// Initialise random number generator, distribution in range [0, 1000000]
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, 1000000);

	double xRandom = -0.5 + dist(rng) / (double)1000000;
	double yRandom = -0.5 + dist(rng) / (double)1000000;

	// Add random variation to particle position and check it remains inside cell
	this->position[0] += parametersList->xPerturbation * xRandom;
	if (this->position[0] < mesh->cellsVector.cells[this->cellID - 1].left ||
		this->position[0] > mesh->cellsVector.cells[this->cellID - 1].right)
	{
		parametersList->logBrief("Particle " + std::to_string(this->particleID) + " has been pushed out of initial cell", 3);
	}

	this->position[1] += parametersList->yPerturbation * yRandom;
	if (this->position[1] < mesh->cellsVector.cells[this->cellID - 1].bottom ||
		this->position[1] > mesh->cellsVector.cells[this->cellID - 1].top)
	{
		parametersList->logBrief("Particle " + std::to_string(this->particleID) + " has been pushed out of initial cell", 3);
	}

	// TODO: Select velocities from a Maxwellian distribution, add third component 
	// of velocity as well for 2D3V simulation
	// Initial particle velocity (uInitial, vInitial)
	velocity.push_back(parametersList->uInitial);	// u
	velocity.push_back(parametersList->vInitial);	// v

	// Extra setup for the two-stream instability problem
	if (parametersList->twoStream)
	{
		this->basic.type = 1;
		if (xRandom >= 0.0)
		{
			this->basic.type = -1;
			this->velocity[0] *= -1.0;
		}
	}
}


// Single particle constructor
Particle::Particle(Parameters *parametersList, Mesh *mesh, int patchID, int cellID, int particleID, std::string type)
{
	this->particleID = particleID;
	this->cellID = cellID;

	if (type == "electron" && (parametersList->simulationType == "full" || parametersList->simulationType == "electron"))
	{
		this->basic.q = ELECTRON_CHARGE;
		this->basic.m = ELECTRON_MASS_kg;
		this->basic.type = -1;
	}
	else if (type == "ion" && (parametersList->simulationType == "full" || parametersList->simulationType == "partial"))
	{
		if (parametersList->propellant == "xenon")
		{
			this->basic.q = -ELECTRON_CHARGE;
			this->basic.m = XENON_MASS_kg - ELECTRON_MASS_kg;
		}
		this->basic.type = 1;
	}
	else if (type == "neutral" && (parametersList->simulationType == "full" || parametersList->simulationType == "partial"))
	{
		if (parametersList->propellant == "xenon")
		{
			this->basic.q = 0.0;
			this->basic.m = XENON_MASS_kg;
		}
		this->basic.type = 0;
	}

	// TODO: Add third component of position, set to zero
	// Place particle in cell at location (xInitial, yInitial)
	position.push_back(mesh->cellsVector.cells[cellID - 1].left * (1 - parametersList->xInitial) +
		mesh->cellsVector.cells[cellID - 1].right * parametersList->xInitial);			// x
	position.push_back(mesh->cellsVector.cells[cellID - 1].top * parametersList->yInitial +
		mesh->cellsVector.cells[cellID - 1].bottom * (1 - parametersList->yInitial));		// y

	// Initialise random number generator, distribution in range [0, 1000000]
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, 1000000);

	double xRandom = -0.5 + dist(rng) / (double)1000000;
	double yRandom = -0.5 + dist(rng) / (double)1000000;

	// Add random variation to particle position and check it remains inside cell

	this->position[0] += parametersList->xPerturbation * xRandom;
	if (this->position[0] < mesh->cellsVector.cells[this->cellID - 1].left ||
		this->position[0] > mesh->cellsVector.cells[this->cellID - 1].right)
	{
		parametersList->logBrief("Particle " + std::to_string(this->particleID) + " has been pushed out of initial cell", 3);
	}
	this->position[1] += parametersList->yPerturbation * yRandom;
	if (this->position[1] < mesh->cellsVector.cells[this->cellID - 1].bottom ||
		this->position[1] > mesh->cellsVector.cells[this->cellID - 1].top)
	{
		parametersList->logBrief("Particle " + std::to_string(this->particleID) + " has been pushed out of initial cell", 3);
	}

	// TODO: Select velocities from a Maxwellian distribution, add third component 
	// of velocity as well for 2D3V simulation
	// Initial particle velocity (uInitial, vInitial)
	velocity.push_back(parametersList->uInitial);	// u
	velocity.push_back(parametersList->vInitial);	// v

	// Extra setup for the two-stream instability problem
	if (parametersList->twoStream)
	{
		this->basic.type = 1;
		if (xRandom >= 0.0)
		{
			this->basic.type = -1;
			this->velocity[0] *= -1.0;
		}
	}
}


// Destructor
Particle::~Particle()
{
}