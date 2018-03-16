//! \file
//! \brief Definition of FDTD class 
//! \author Rahul Kalampattel
//! \date Last updated March 2018

#pragma once

#include "Parameters.h"
#include "Mesh.h"

//! \class FDTD
//! \brief Resolves an external EM field using the FDTD method
class FDTD
{
public:
	// Data members


	// Constructor/destructor
	FDTD();											//!< Default constructor
	FDTD(Parameters *parametersList, Mesh *mesh);	//!< Constructor
	~FDTD();										//!< Destructor


	// Methods

};