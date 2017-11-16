//! \file
//! \brief Implementation of Mesh class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#include "Parameters.h"
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

	for (int i = 0; i < cellsVector.cells.size(); i++)
	{
		// Only need to check two opposite nodes to find left, right, top and bottom,
		// however in order to be sure that a set of nodes contains two opposites, 
		// need at least three of them (two opposites plus one adjacent, hence i<3)
		
		for (int j = 0; j < 3; j++)
			
		{
			int nodeID = cellsVector.cells[i].connectivity.nodeIDs[j] - 1;
			// The nodeIDs are indexed from 1, but the nodes vector from 0, hence the -1 above

			double x = nodesVector.nodes[nodeID].geometry.X.element(0, 0);
			double y = nodesVector.nodes[nodeID].geometry.X.element(1, 0);


			if (j == 0)
			{
				cellsVector.cells[i].left = x;
				cellsVector.cells[i].right = x;
				cellsVector.cells[i].top = y;
				cellsVector.cells[i].bottom = y;
			}
			else
			{
				if (x < cellsVector.cells[i].left)
				{
					cellsVector.cells[i].left = x;
				}
				else if (x > cellsVector.cells[i].right)
				{
					cellsVector.cells[i].right = x;
				}
				if (y < cellsVector.cells[i].bottom)
				{
					cellsVector.cells[i].bottom = y;
				}
				else if (y > cellsVector.cells[i].top)
				{
					cellsVector.cells[i].top = y;
				}
			}
		}

		int firstNodeID = cellsVector.cells[i].connectivity.nodeIDs[0] - 1;	// First node
		double x = nodesVector.nodes[firstNodeID].geometry.X.element(0, 0);
		double y = nodesVector.nodes[firstNodeID].geometry.X.element(1, 0);
		int faceID;

		if (x == cellsVector.cells[i].left && y == cellsVector.cells[i].bottom)	// Bottom left node
		{
			faceID = cellsVector.cells[i].connectivity.faceIDs[0] - 1;
			cellsVector.cells[i].bottomCellID = facesVector.faces[faceID].connectivity.cl[0] +
				facesVector.faces[faceID].connectivity.cr[0] - i - 2;

			faceID = cellsVector.cells[i].connectivity.faceIDs[1] - 1;
			cellsVector.cells[i].rightCellID = facesVector.faces[faceID].connectivity.cl[0] +
				facesVector.faces[faceID].connectivity.cr[0] - i - 2;

			faceID = cellsVector.cells[i].connectivity.faceIDs[2] - 1;
			cellsVector.cells[i].topCellID = facesVector.faces[faceID].connectivity.cl[0] +
				facesVector.faces[faceID].connectivity.cr[0] - i - 2;

			faceID = cellsVector.cells[i].connectivity.faceIDs[3] - 1;
			cellsVector.cells[i].leftCellID = facesVector.faces[faceID].connectivity.cl[0] +
				facesVector.faces[faceID].connectivity.cr[0] - i - 2;
		}
		/*
		else if (x == cellsVector.cells[i].left && y == cellsVector.cells[i].top)	// Top left node
		{

		}
		else if (x == cellsVector.cells[i].right && y == cellsVector.cells[i].bottom) // Bottom right node
		{

		}
		else if (x == cellsVector.cells[i].right && y == cellsVector.cells[i].top)	// Top right node
		{

		}
		*/

	}
}

// Destructor
Mesh::~Mesh()
{
}

void Mesh::addParticlesToCell(int cellID, int particleID)
{
	cellsVector.cells[cellID].listOfParticles.push_back(particleID);
}
