//! \file
//! \brief Implementation of ParticlePusher class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#include "ParticlePusher.h"

// Default constructor
ParticlePusher::ParticlePusher(Parameters *parametersList, Mesh *mesh, VectorParticle *particlesVector)
{
	for (int i = 0; i < particlesVector->numParticles; i++)
	{
		// Update x and y positions
		particlesVector->particleVector[i].position[0] += parametersList->timeStep * particlesVector->particleVector[i].velocity[0]; 
		particlesVector->particleVector[i].position[1] += parametersList->timeStep * particlesVector->particleVector[i].velocity[1];

		// The following assumes the particle does not travel out of the cell to 
		// a diagonally adjacent cell (i.e. it only moves left, right, up or down 
		// in a single time step)
		
		if (particlesVector->particleVector[i].position[0] < 
			mesh->cellsVector.cells[particlesVector->particleVector[i].cellID].left)	// Exit left
		{
			particlesVector->particleVector[i].cellID = 
				mesh->cellsVector.cells[particlesVector->particleVector[i].cellID].leftCellID;
		}
		else if (particlesVector->particleVector[i].position[0] > 
			mesh->cellsVector.cells[particlesVector->particleVector[i].cellID].right)	// Exit right
		{
			particlesVector->particleVector[i].cellID = 
				mesh->cellsVector.cells[particlesVector->particleVector[i].cellID].rightCellID;
		}
		else if (particlesVector->particleVector[i].position[1] < 
			mesh->cellsVector.cells[particlesVector->particleVector[i].cellID].bottom)	// Exit bottom
		{
			particlesVector->particleVector[i].cellID = 
				mesh->cellsVector.cells[particlesVector->particleVector[i].cellID].bottomCellID;
		}
		else if (particlesVector->particleVector[i].position[1] > 
			mesh->cellsVector.cells[particlesVector->particleVector[i].cellID].top)	// Exit top
		{
			particlesVector->particleVector[i].cellID = 
				mesh->cellsVector.cells[particlesVector->particleVector[i].cellID].topCellID;
		}

		particlesVector->updatePositionVector(&particlesVector->particleVector[i]);
	}
}

// Destructor
ParticlePusher::~ParticlePusher()
{
}