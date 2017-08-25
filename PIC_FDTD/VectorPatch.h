#pragma once

#include "Patch.h"
#include <vector>

class VectorPatch
{
public:
	VectorPatch(Parameters parametersList);
	~VectorPatch();
	void startPIC();

	vector<Patch> patchesVector;
};