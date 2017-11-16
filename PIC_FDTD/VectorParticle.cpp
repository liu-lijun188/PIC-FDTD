//! \file
//! \brief Implementation of VectorParticle class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#include "VectorParticle.h"

// Default constructor
VectorParticle::VectorParticle()
{
}

// Constructor
VectorParticle::VectorParticle(Parameters *parametersList, Mesh *mesh, int patchID)
{
	parametersList->logMessages("Creating particles vector in patch " + std::to_string(patchID), __FILE__, __LINE__);
	
	//for (int i = 0; i < mesh->numCells; i++)
	int numCellsWithParticles = 2;
	for (int i = 0; i <mesh->numCells; i++)	// Single particle
	{
		for (int j = 0; j < parametersList->particlesPerCell; j++)
		{
			Particle particle(parametersList, mesh, patchID, i, j);
			particleVector.push_back(particle);
			numParticles += 1;
			positionVector.push_back(particle.position);
			positionVector[particle.cellID].push_back(particle.cellID);
			positionVector[particle.cellID].push_back(particle.particleID);
			mesh->addParticlesToCell(particle.cellID, particle.particleID);
		}
	}
}

// Destructor
VectorParticle::~VectorParticle()
{
}

void VectorParticle::updatePositionVector(Particle *particle)
{
	positionVector.pop_back();
	positionVector.push_back(particle->position);
	positionVector[particle->cellID].push_back(particle->particleID);
}
