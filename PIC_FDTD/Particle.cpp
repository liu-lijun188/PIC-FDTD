//! \file
//! \brief Implementation of Particle class 
//! \author Rahul Kalampattel
//! \date Last updated November 2017

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

	// Place particle in middle of cell
	position.push_back((mesh->cellsVector.cells[cellID].left + 
		mesh->cellsVector.cells[cellID].right) / 2);			// x
	position.push_back((mesh->cellsVector.cells[cellID].top + 
		mesh->cellsVector.cells[cellID].bottom) / 2);			// y
	
	velocity.push_back(0.1);	// u
	velocity.push_back(0.1);	// v
}


// Destructor
Particle::~Particle()
{
}