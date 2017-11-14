//! \file
//! \brief Definition of ParticlePusher class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#pragma once

#include "Mesh.h"
#include "Parameters.h"
#include "VectorParticle.h"

//! \class ParticlePusher
//! \brief Definition
class ParticlePusher
{
public:
	ParticlePusher(Parameters *parametersList, Mesh *mesh, VectorParticle *particlesVector);	//!< Default constructor
	~ParticlePusher();	//!< Destructor
};