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
	VectorParticle();									//!< Default constructor
	VectorParticle(Parameters *localParametersList);	//!< Constructor
	~VectorParticle();									//!< Destructor

	vector<Particle> particleVector;
};