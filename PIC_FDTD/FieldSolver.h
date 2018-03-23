//! \file
//! \brief Definition of FieldSolver class 
//! \author Rahul Kalampattel
//! \date Last updated March 2018

#pragma once

#include "Mesh.h"
#include "Parameters.h"
#include "VectorParticle.h"

//! \class FieldSolver
//! \brief Solves the Poisson equation
class FieldSolver
{
public:
	// Data members


	// Constructor/destructor
	FieldSolver();										//!< Default constructor
	FieldSolver(Parameters *parametersList, Mesh *mesh);//!< Constructor
	~FieldSolver();										//!< Destructor

	
	// Methods

};