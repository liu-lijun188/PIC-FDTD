//! \file
//! \brief Implementation of VectorParticle class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#include "VectorParticle.h"

VectorParticle::VectorParticle()
{
}

VectorParticle::VectorParticle(Parameters *localParametersList, int patchID)
{
	localParametersList->logMessages("Creating particles vector in patch " + std::to_string(patchID), __FILE__, __LINE__);
	for (int i = 0; i < localParametersList->particlesPerPatch; i++)
	{
		Particle particle(localParametersList);
		particleVector.push_back(particle);
	}
}


VectorParticle::~VectorParticle()
{
}