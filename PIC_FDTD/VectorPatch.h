//! \file
//! \brief Definition of VectorPatch class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#pragma once

#include "Patch.h"
#include <vector>

//! \class VectorPatch
//! \brief Definition
class VectorPatch
{
public:
	VectorPatch();								//!< Default constructor
	VectorPatch(Parameters parametersList);		//!< Constructor
	~VectorPatch();								//!< Destructor
	void startPIC();							//!< Start the PIC loop within a VectorPatch object

	vector<Patch> patchesVector;
};