//! \file
//! \brief Implementation of Particle class 
//! \author Rahul Kalampattel
//! \date Last updated March 2018

#include "Particle.h"

// Default constructor
Particle::Particle()
{
}


// Constructor
Particle::Particle(Parameters *parametersList, Mesh *mesh, int patchID, int cellID, int particleID, int index)
{
	this->particleID = particleID;
	this->cellID = cellID;
	this->basic.q = parametersList->charge;
	this->basic.m = parametersList->mass;

	if (parametersList->particlesPerCell == 1)
	{
		// Place particle in cell at location (xTest, yTest)
		position.push_back(mesh->cellsVector.cells[cellID - 1].left * (1 - parametersList->xTest) +
			mesh->cellsVector.cells[cellID - 1].right * parametersList->xTest);			// x
		position.push_back(mesh->cellsVector.cells[cellID - 1].top * parametersList->yTest +
			mesh->cellsVector.cells[cellID - 1].bottom * (1 - parametersList->yTest));		// y
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

	// Initial particle velocity (uTest, vTest)
	velocity.push_back(parametersList->uTest);	// u
	velocity.push_back(parametersList->vTest);	// v

	// Extra setup for the two-stream instability problem
	if (parametersList->twoStream == 1)
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

// TODO: Implement methods to create/destroy particles over time in the simulation, 
// placing them in the desired location and identifying the relevant cell, while 
// updating all relevant parameters (numParticles, particlesVector, plotVector, etc.)