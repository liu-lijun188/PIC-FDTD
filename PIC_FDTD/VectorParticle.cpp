//! \file
//! \brief Implementation of VectorParticle class 
//! \author Rahul Kalampattel
//! \date Last updated March 2018

#include "VectorParticle.h"

// Default constructor
VectorParticle::VectorParticle()
{
}


// Constructor
VectorParticle::VectorParticle(Parameters *parametersList, Mesh *mesh, int patchID)
{
	parametersList->logMessages("Creating particles vector in patch " + std::to_string(patchID), __FILE__, __LINE__, 1);
	
	// If 0 < numCellsWithParticles <= numCells, seed particles in a few cells, 
	// else seed particles in every cell
	if (parametersList->numCellsWithParticles < 1 || 
		parametersList->numCellsWithParticles > mesh->numCells)
	{
		parametersList->logBrief("Value of numCellsWithParticles has been changed", 2);
		parametersList->numCellsWithParticles = mesh->numCells;
	}

	for (int i = 0; i < parametersList->numCellsWithParticles; i++)
	{
		// Check if particlesPerCell is a square number
		if (sqrt(parametersList->particlesPerCell) != round(sqrt(parametersList->particlesPerCell)))
		{
			parametersList->logBrief("Value of particlesPerCell has been changed", 2);
			parametersList->particlesPerCell = 1;
		}
		
		for (int j = 0; j < parametersList->particlesPerCell; j++)
		{
			numParticles++;

			Particle particle(parametersList, mesh, patchID, i + 1, numParticles, j);
			particleVector.push_back(particle);

			plotVector.push_back(particle.position);
			plotVector.back().push_back(particle.velocity[0]);
			plotVector.back().push_back(particle.velocity[1]);
			plotVector.back().push_back(particle.cellID);
			plotVector.back().push_back(particle.particleID);
			plotVector.back().push_back(particle.basic.type);

			mesh->addParticlesToCell(particle.cellID, particle.particleID);
		}
		
	}
	parametersList->logMessages("Generated " + std::to_string(numParticles) +
		" particles in " + std::to_string(parametersList->numCellsWithParticles) + 
		" cells", __FILE__, __LINE__, 1);
}


// Destructor
VectorParticle::~VectorParticle()
{
}


// Update state of plotVector
void VectorParticle::updatePlotVector(Particle *particle)
{
	// Resizing vectors is not a particularly efficient operation, consider some
	// other means of storing data for plotting in future

	for (int i = 0; i < plotVector.size(); i++)
	{
		if (plotVector[i][5] == static_cast<double>(particle->particleID))
		{
			plotVector.insert(plotVector.begin() + i, particle->position);
			plotVector[i].push_back(particle->velocity[0]);
			plotVector[i].push_back(particle->velocity[1]);
			plotVector[i].push_back(particle->cellID);
			plotVector[i].push_back(particle->particleID);
			plotVector[i].push_back(particle->basic.type);
			plotVector.erase(plotVector.begin() + i + 1);
		}
	}
}


// Clear fields and lorentz members of particleVector
void VectorParticle::clearFields()
{
	for (int i = 0; i < numParticles; i++)
	{
		particleVector[i].fields = { 0.0,0.0,0.0,0.0 };
		particleVector[i].lorentz = { 0.0, 0.0 };
	}
}
