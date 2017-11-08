//! \file
//! \brief Implementation of Mesh class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#include "Mesh.h"

// Default constructor
Mesh::Mesh()
{
}

// Constructor
Mesh::Mesh(Parameters *localParametersList)
{
	numCells = localParametersList->gridinfo.NCM;
	numFaces = localParametersList->gridinfo.NFM;
	numGhost = localParametersList->gridinfo.NGM;
	numNodes = localParametersList->gridinfo.NNM;
	dimension = localParametersList->gridinfo.DIM;
	
	cellsVector.allocate(localParametersList->gridgeo.cells);
	facesVector.allocate(localParametersList->gridgeo.faces);
	ghostVector.allocate(localParametersList->gridgeo.ghost);
	nodesVector.allocate(localParametersList->gridgeo.nodes);
}

// Destructor
Mesh::~Mesh()
{
}