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
Particle::Particle(Parameters *parametersList, Mesh *mesh, int patchID, int cellID, int particleID)
{
	parametersList->logMessages("Generating particle " + std::to_string(particleID) + 
		" in cell " + std::to_string(cellID) + " in patch " + std::to_string(patchID),
		__FILE__, __LINE__);
	
	this->particleID = particleID;
	this->cellID = cellID;
	this->basic.q = parametersList->charge;

	// Place particle in cell (xTest, yTest)
	position.push_back(mesh->cellsVector.cells[cellID - 1].left * (1 - parametersList->xTest) + 
		mesh->cellsVector.cells[cellID - 1].right * (parametersList->xTest));			// x
	position.push_back(mesh->cellsVector.cells[cellID - 1].top * (parametersList->yTest) +
		mesh->cellsVector.cells[cellID - 1].bottom * (1 - parametersList->yTest));		// y
	
	// Initial particle velocity (uTest, vTest)
	velocity.push_back(parametersList->uTest);	// u
	velocity.push_back(parametersList->vTest);	// v
}


// Destructor
Particle::~Particle()
{
}