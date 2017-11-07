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
VectorParticle::VectorParticle(Parameters *parametersList, int patchID)
{
	parametersList->logMessages("Creating particles vector in patch " + std::to_string(patchID), __FILE__, __LINE__);

	vector2D data;
	
	for (int i = 0; i < parametersList->gridinfo.NCM; i++)
	{
		for (int j = 0; j < parametersList->particlesPerCell; j++)
		{
			Particle particle(parametersList, patchID, i, j);
			particleVector.push_back(particle);
			data.push_back(particle.position);
			data[i].push_back(i);
		}
	}
	
	parametersList->generateOutput(data, parametersList->gridinfo.NCM);
}

// Destructor
VectorParticle::~VectorParticle()
{
}