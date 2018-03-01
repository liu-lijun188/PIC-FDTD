//! \file
//! \brief Definition of VectorPatch class 
//! \author Rahul Kalampattel
//! \date Last updated March 2018

#pragma once

#include "Patch.h"

//! \class VectorPatch
//! \brief Create and manage a vector of Patch objects
class VectorPatch
{
public:
	// Data members
	int numErrors = 0;							//!< Sum of errors in Patch objects
	std::vector<Patch> patchesVector;			//!< Vector of Patch objects


	// Constructor/destructor
	VectorPatch();								//!< Default constructor
	VectorPatch(Parameters *parametersList);	//!< Constructor
	~VectorPatch();								//!< Destructor
	

	// Methods
	void startPIC();							//!< Start the PIC loop within a VectorPatch object
};