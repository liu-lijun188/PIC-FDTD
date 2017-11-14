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

		particlesVector->updatePositionVector(&particlesVector->particleVector[i]);
	}
}

// Destructor
ParticlePusher::~ParticlePusher()
{
}