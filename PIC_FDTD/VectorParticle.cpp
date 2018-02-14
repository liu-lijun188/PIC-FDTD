//! \file
//! \brief Implementation of VectorParticle class 
//! \author Rahul Kalampattel
//! \date Last updated February 2018

#include "VectorParticle.h"

// Default constructor
VectorParticle::VectorParticle()
{
}


// Constructor
VectorParticle::VectorParticle(Parameters *parametersList, Mesh *mesh, int patchID)
{
	parametersList->logMessages("Creating particles vector in patch " + std::to_string(patchID), __FILE__, __LINE__);

	//for (int i = 0; i < mesh->numCells; i++)							// Particle in every cell
	for (int i = 0; i < parametersList->numCellsWithParticles; i++)		// Particle in a few cells
	{
		for (int j = 0; j < parametersList->particlesPerCell; j++)
		{
			numParticles++;

			Particle particle(parametersList, mesh, patchID, i, numParticles);
			particleVector.push_back(particle);

			positionVector.push_back(particle.position);
			positionVector.back().push_back(particle.cellID);
			positionVector.back().push_back(particle.particleID);

			mesh->addParticlesToCell(particle.cellID, particle.particleID);
		}
	}
}


// Destructor
VectorParticle::~VectorParticle()
{
}


// Update state of positionVector
void VectorParticle::updatePositionVector(Particle *particle)
{
	// Resizing vectors is not a particularly efficient operation, consider some
	// other means of storing data for plotting in future

	for (int i = 0; i < positionVector.size(); i++)
	{
		if (positionVector[i][3] == static_cast<double>(particle->particleID))
		{
			positionVector.insert(positionVector.begin() + i, particle->position);
			positionVector[i].push_back(particle->cellID);
			positionVector[i].push_back(particle->particleID);
			positionVector.erase(positionVector.begin() + i + 1);
		}
	}
}
