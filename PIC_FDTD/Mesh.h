#pragma once

#include "Parameters.h"

class Mesh
{
public:
	Mesh();
	Mesh(Parameters *localParametersList);
	~Mesh();
	void checkMesh();
	Parameters localParametersList;
};