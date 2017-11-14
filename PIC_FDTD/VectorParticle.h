//! \file
//! \brief Definition of VectorParticle class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#pragma once

#include "Particle.h"

//! \class VectorParticle
//! \brief Definition
class VectorParticle
{
public:
	VectorParticle();							//!< Default constructor
	VectorParticle(Parameters *parametersList,
		Mesh *mesh, int patchID);				//!< Constructor
	~VectorParticle();							//!< Destructor

	void updatePositionVector(Particle *particle);

	std::vector<Particle> particleVector;
	int numParticles = 0;
	vector2D positionVector;
};