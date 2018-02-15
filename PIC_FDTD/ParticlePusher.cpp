//! \file
//! \brief Implementation of ParticlePusher class 
//! \author Rahul Kalampattel
//! \date Last updated February 2018

#include "ParticlePusher.h"

// Default constructor
ParticlePusher::ParticlePusher()
{
}

// Constructor
ParticlePusher::ParticlePusher(Parameters *parametersList, Mesh *mesh, VectorParticle *particlesVector)
{
	for (int i = 0; i < particlesVector->numParticles; i++)
	{
		// Update x position
		particlesVector->particleVector[i].position[0] += 
			parametersList->timeStep * particlesVector->particleVector[i].velocity[0]; 

		// Update cell ID in x direction
		if (particlesVector->particleVector[i].position[0] < 
			mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].left)	// Exit left
		{
			mesh->removeParticlesFromCell(particlesVector->particleVector[i].cellID,
				particlesVector->particleVector[i].particleID);
			
			particlesVector->particleVector[i].cellID = 
				mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].leftCellID;

			mesh->addParticlesToCell(particlesVector->particleVector[i].cellID,
				particlesVector->particleVector[i].particleID);
		}
		else if (particlesVector->particleVector[i].position[0] > 
			mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].right)	// Exit right
		{
			mesh->removeParticlesFromCell(particlesVector->particleVector[i].cellID,
				particlesVector->particleVector[i].particleID);
			
			particlesVector->particleVector[i].cellID = 
				mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].rightCellID;

			mesh->addParticlesToCell(particlesVector->particleVector[i].cellID,
				particlesVector->particleVector[i].particleID);
		}

		// Update y position
		particlesVector->particleVector[i].position[1] +=
			parametersList->timeStep * particlesVector->particleVector[i].velocity[1];

		// Update cell ID in y direction
		if (particlesVector->particleVector[i].position[1] < 
			mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].bottom)	// Exit bottom
		{
			mesh->removeParticlesFromCell(particlesVector->particleVector[i].cellID,
				particlesVector->particleVector[i].particleID);
			
			particlesVector->particleVector[i].cellID = 
				mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].bottomCellID;

			mesh->addParticlesToCell(particlesVector->particleVector[i].cellID,
				particlesVector->particleVector[i].particleID);
		}
		else if (particlesVector->particleVector[i].position[1] > 
			mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].top)	// Exit top
		{
			mesh->removeParticlesFromCell(particlesVector->particleVector[i].cellID,
				particlesVector->particleVector[i].particleID);
			
			particlesVector->particleVector[i].cellID = 
				mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].topCellID;

			mesh->addParticlesToCell(particlesVector->particleVector[i].cellID,
				particlesVector->particleVector[i].particleID);
		}

		particlesVector->updatePositionVector(&particlesVector->particleVector[i]);
	}
}


// Destructor
ParticlePusher::~ParticlePusher()
{
}