//! \file
//! \brief Definition of MCC class 
//! \author Rahul Kalampattel
//! \date Last updated March 2018

#pragma once

#include "Mesh.h"
#include "Parameters.h"
#include "VectorParticle.h"

//! \class MCC
//! \brief Handles collisions between particles
class MCC
{
public:
	// Data members


	// Constructor/destructor
	MCC();									//!< Default constructor
	MCC(Parameters *parametersList, Mesh *mesh,
		VectorParticle *particlesVector);	//!< Constructor
	~MCC();									//!< Destructor


	// Methods

};