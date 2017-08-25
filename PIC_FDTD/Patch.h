#pragma once

#include <iostream>

#include "ChargeProjector.h"
#include "FDTD.h"
#include "FieldInterpolator.h"
#include "FieldSolver.h"
#include "MCC.h"
#include "Mesh.h"
#include "Parameters.h"
#include "ParticlePusher.h"
#include "VectorParticle.h"

using namespace std;

class Patch
{
public:
	Patch(Parameters parametersList);
	~Patch();
	void startPIC();

	Parameters localParametersList;
	Mesh mesh;
	VectorParticle particlesVector;
};