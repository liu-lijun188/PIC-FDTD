//! \file
//! \brief Definition of FieldInterpolator class 
//! \author Rahul Kalampattel
//! \date Last updated March 2018

#pragma once

#include "Mesh.h"
#include "Parameters.h"
#include "VectorParticle.h"

//! \class FieldInterpolator
//! \brief Interpolate quantities from mesh to particle locations
class FieldInterpolator
{
public:
	// Data members


	// Constructor/destructor
	FieldInterpolator();								//!< Default constructor
	FieldInterpolator(Parameters *parametersList,
		Mesh *mesh, VectorParticle *particlesVector);	//!< Constructor
	~FieldInterpolator();								//!< Destructor


	// Methods

};