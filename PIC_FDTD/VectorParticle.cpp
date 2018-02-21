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
	
	// If 0 < numCellsWithParticles < numCells, seed particles in a few cells, 
	// else seed in every cell
	if (parametersList->numCellsWithParticles < 1 || 
		parametersList->numCellsWithParticles > mesh->numCells)
	{
		parametersList->numCellsWithParticles = mesh->numCells;
	}

	for (int i = 0; i < parametersList->numCellsWithParticles; i++)
	{
		// Check is particlesPerCell is a square number
		if (sqrt(parametersList->particlesPerCell)  == round(sqrt(parametersList->particlesPerCell)))
		{
			for (int j = 0; j < parametersList->particlesPerCell; j++)
			{
				numParticles++;

				Particle particle(parametersList, mesh, patchID, i + 1, numParticles, j);
				particleVector.push_back(particle);

				positionVector.push_back(particle.position);
				positionVector.back().push_back(particle.cellID);
				positionVector.back().push_back(particle.particleID);

				mesh->addParticlesToCell(particle.cellID, particle.particleID);
			}
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
