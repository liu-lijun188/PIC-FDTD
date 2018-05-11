//! \file
//! \brief Definition of ChargeProjector class 
//! \author Rahul Kalampattel
//! \date Last updated November 2017

#pragma once

#include "Mesh.h"
#include "Parameters.h"
#include "VectorParticle.h"

//! \class ChargeProjector
//! \brief Projects quantities from particle to mesh locations
class ChargeProjector
{
public:
	// Data members


	// Constructor/destructor
	ChargeProjector();									//!< Default constructor
	ChargeProjector(Parameters *parametersList,
		Mesh *mesh, VectorParticle *particlesVector);	//!< Constructor
	~ChargeProjector();									//!< Destructor


	// Methods

};