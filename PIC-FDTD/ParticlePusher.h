//! \file
//! \brief Definition of ParticlePusher class 
//! \author Rahul Kalampattel
//! \date Last updated February 2018

#pragma once

#include "Mesh.h"
#include "Parameters.h"
#include "VectorParticle.h"

//! \class ParticlePusher
//! \brief Update particle position and velocity at each time step
class ParticlePusher
{
public:
	// Data members


	// Constructor/destructor
	ParticlePusher();									//!< Default constructor
	ParticlePusher(Parameters *parametersList, Mesh *mesh, 
		VectorParticle *particlesVector, double time);	//!< Constructor
	~ParticlePusher();									//!< Destructor


	// Methods

};