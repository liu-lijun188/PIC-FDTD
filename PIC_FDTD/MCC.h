//! \file
//! \brief Definition of MCC class 
//! \author Rahul Kalampattel
//! \date Last updated March 2018

#pragma once

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
	MCC(Parameters *parametersList, 
		VectorParticle *particlesVector);	//!< Constructor
	~MCC();									//!< Destructor


	// Methods

};