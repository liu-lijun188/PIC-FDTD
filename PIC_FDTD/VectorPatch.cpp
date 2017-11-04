//! \file
//! \brief Implementation of VectorPatch class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#include "VectorPatch.h"

VectorPatch::VectorPatch()
{
}

VectorPatch::VectorPatch(Parameters parametersList)
{
	parametersList.logMessages("Creating patches vector...");
	for (int i = 0; i < parametersList.numberOfPatches; i++)
	{
		cout << "Patch " << i << endl;
		Patch patch(parametersList);
		patchesVector.push_back(patch);
	}
}

VectorPatch::~VectorPatch()
{
}

void VectorPatch::startPIC()
{
	for (unsigned int i = 0; i < patchesVector.size(); i++)
	{
		cout << "Working in patch " << i << endl;
		patchesVector[i].startPIC();
	}
}