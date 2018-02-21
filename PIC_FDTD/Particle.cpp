//! \file
//! \brief Implementation of Particle class 
//! \author Rahul Kalampattel
//! \date Last updated February 2018

#include "Particle.h"

// Default constructor
Particle::Particle()
{
}


// Constructor
Particle::Particle(Parameters *parametersList, Mesh *mesh, int patchID, int cellID, int particleID, int index)
{
	parametersList->logMessages("Generating particle " + std::to_string(particleID) + 
		" in cell " + std::to_string(cellID) + " in patch " + std::to_string(patchID),
		__FILE__, __LINE__);
	
	this->particleID = particleID;
	this->cellID = cellID;
	this->basic.q = parametersList->charge;

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

	// TODO: Add some random perturbation to the initial position, but need to 
	// make sure that the particle remains inside the simulation domain

	// Initial particle velocity (uTest, vTest)
	velocity.push_back(parametersList->uTest);	// u
	velocity.push_back(parametersList->vTest);	// v

}


// Destructor
Particle::~Particle()
{
}