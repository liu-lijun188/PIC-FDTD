//! \file
//! \brief Implementation of VectorParticle class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#include "VectorParticle.h"

VectorParticle::VectorParticle()
{
}

VectorParticle::VectorParticle(Parameters *parametersList, int patchID)
{
	parametersList->logMessages("Creating particles vector in patch " + std::to_string(patchID), __FILE__, __LINE__);
//	for (int i = 0; i < parametersList->gridinfo.NCM; i++)
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < parametersList->particlesPerCell; j++)
		{
			Particle particle(parametersList, patchID, i, j);
			particleVector.push_back(particle);
		}
	}

}


VectorParticle::~VectorParticle()
{
}