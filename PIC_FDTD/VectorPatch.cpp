//! \file
//! \brief Implementation of VectorPatch class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#include "VectorPatch.h"

// Default constructor
VectorPatch::VectorPatch()
{
}

// Constructor
VectorPatch::VectorPatch(Parameters parametersList)
{
	parametersList.logMessages("Creating patches vector", __FILE__, __LINE__);
	for (int i = 0; i < parametersList.numberOfPatches; i++)
	{
		Patch patch(parametersList, i);
		patchesVector.push_back(patch);
	}
}

// Destructor
VectorPatch::~VectorPatch()
{
}

// Start the PIC loop within a VectorPatch object
void VectorPatch::startPIC()
{
	for (unsigned int i = 0; i < patchesVector.size(); i++)
	{
		patchesVector[i].startPIC();
	}
}