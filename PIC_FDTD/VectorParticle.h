#pragma once
#include "Particle.h"

class VectorParticle
{
public:
	VectorParticle();
	VectorParticle(Parameters *localParametersList);
	~VectorParticle();

	vector<Particle> particleVector;
};