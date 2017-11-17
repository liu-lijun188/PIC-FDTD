//! \file
//! \brief Implementation of VectorParticle class 
//! \author Rahul Kalampattel
//! \date Last updated November 2017

#include "VectorParticle.h"

// Default constructor
VectorParticle::VectorParticle()
{
}


// Constructor
VectorParticle::VectorParticle(Parameters *parametersList, Mesh *mesh, int patchID)
{
	parametersList->logMessages("Creating particles vector in patch " + std::to_string(patchID), __FILE__, __LINE__);

	//for (int i = 0; i < mesh->numCells; i++)	// Particle in every cell
	int numCellsWithParticles = 1;				// Particle in a single cell
	for (int i = 0; i < numCellsWithParticles; i++)	
	{
		for (int j = 0; j < parametersList->particlesPerCell; j++)
		{
			Particle particle(parametersList, mesh, patchID, i, j);
			particleVector.push_back(particle);

			positionVector.push_back(particle.position);
			positionVector[i].push_back(particle.cellID);
			positionVector[i].push_back(particle.particleID);

			mesh->addParticlesToCell(particle.cellID, particle.particleID);
		}
	}

	numParticles = particleVector.size();
}


// Destructor
VectorParticle::~VectorParticle()
{
}


// Update state of positionVector
void VectorParticle::updatePositionVector(Particle *particle)
{
	positionVector.pop_back();
	positionVector.push_back(particle->position);

	// Currently set up for single cell testing, otherwise need to identify the
	// correct cell in which to push_back
	positionVector[0].push_back(particle->cellID);
	positionVector[0].push_back(particle->particleID);
}
