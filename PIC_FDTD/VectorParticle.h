//! \file
//! \brief Definition of VectorParticle class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#pragma once

#include "Particle.h"
#include "Mesh.h"

//! \class VectorParticle
//! \brief Definition
class VectorParticle
{
public:
	VectorParticle();							//!< Default constructor
	VectorParticle(Parameters *parametersList,
		Mesh *mesh, int patchID);				//!< Constructor
	~VectorParticle();							//!< Destructor

	std::vector<Particle> particleVector;
	vector2D positionVector;
};