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
	this->basic.q = parametersList->charge;

	// Place particle in middle of cell (0.5 ,0.5)
	position.push_back((mesh->cellsVector.cells[cellID].left +
		mesh->cellsVector.cells[cellID].right) / 2);			// x
	position.push_back((mesh->cellsVector.cells[cellID].top +
		mesh->cellsVector.cells[cellID].bottom) / 2);			// y

	// Place particle in lower left quadrant of cell (0.25, 0.25)
	//position.push_back((mesh->cellsVector.cells[cellID].left) * 0.75 + 
	//	(mesh->cellsVector.cells[cellID].right) * 0.25);			// x
	//position.push_back((mesh->cellsVector.cells[cellID].top) * 0.25 + 
	//	(mesh->cellsVector.cells[cellID].bottom) * 0.75);			// y

	// Place particle in upper right quadrant of cell (0.75, 0.75)
	//position.push_back((mesh->cellsVector.cells[cellID].left) * 0.25 +
	//	(mesh->cellsVector.cells[cellID].right) * 0.75);			// x
	//position.push_back((mesh->cellsVector.cells[cellID].top) * 0.75 +
	//	(mesh->cellsVector.cells[cellID].bottom) * 0.25);			// y
	
	velocity.push_back(0);	// u
	velocity.push_back(0);	// v
}


// Destructor
Particle::~Particle()
{
}