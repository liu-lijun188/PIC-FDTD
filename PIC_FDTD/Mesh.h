//! \file
//! \brief Definition of Mesh class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#pragma once

#include "Parameters.h"
#include "VectorCell.h"
#include "VectorFace.h"
#include "VectorGhost.h"
#include "VectorNode.h"

//! \class Mesh
//! \brief Definition
class Mesh
{
public:
	Mesh();										//!< Default constructor
	Mesh(Parameters *localParametersList);		//!< Constructor
	~Mesh();									//!< Destructor

	int numCells, numFaces, numGhost, numNodes, dimension;
	VectorCell cellsVector;
	VectorFace facesVector;
	VectorGhost ghostVector;
	VectorNode nodesVector;
};