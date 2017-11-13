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
	
	for (int i = 0; i < mesh->numCells; i++)
	{
		for (int j = 0; j < parametersList->particlesPerCell; j++)
		{
			Particle particle(parametersList, patchID, i, j);
			particleVector.push_back(particle);
			positionVector.push_back(particle.position);
			positionVector[i].push_back(i);
		}
	}
}

// Destructor
VectorParticle::~VectorParticle()
{
}