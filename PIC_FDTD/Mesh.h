//! \file
//! \brief Definition of Mesh class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#pragma once


#include "VectorCell.h"
#include "VectorFace.h"
#include "VectorGhost.h"
#include "VectorNode.h"

class Parameters;		// Forward declaration to resolve circular dependency

//! \class Mesh
//! \brief Definition
class Mesh
{
public:
	Mesh();										//!< Default constructor
	Mesh(Parameters *localParametersList);		//!< Constructor
	~Mesh();									//!< Destructor

	void addParticlesToCell(int cellID, int particleID);

	int numCells, numFaces, numGhost, numNodes, dimension;
	VectorCell cellsVector;
	VectorFace facesVector;
	VectorGhost ghostVector;
	VectorNode nodesVector;
};