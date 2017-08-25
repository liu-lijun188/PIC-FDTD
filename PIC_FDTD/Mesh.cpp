#include "Mesh.h"

Mesh::Mesh()
{
}


Mesh::Mesh(Parameters *localParametersList)
{
	this->localParametersList = *localParametersList;
}


Mesh::~Mesh()
{
}

void Mesh::checkMesh()
{
	localParametersList.logMessages("Checking mesh...");
}
