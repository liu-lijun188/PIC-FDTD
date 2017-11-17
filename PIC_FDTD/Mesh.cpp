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
		
		int faceID_1 = cellsVector.cells[i].connectivity.faceIDs[0] - 1;
		int leftCell_1 = facesVector.faces[faceID_1].connectivity.cl[0] - 1;
		int rightCell_1 = facesVector.faces[faceID_1].connectivity.cr[0] - 1;

		int faceID_2 = cellsVector.cells[i].connectivity.faceIDs[1] - 1;
		int leftCell_2 = facesVector.faces[faceID_2].connectivity.cl[0] - 1;
		int rightCell_2 = facesVector.faces[faceID_2].connectivity.cr[0] - 1;

		int faceID_3 = cellsVector.cells[i].connectivity.faceIDs[2] - 1;
		int leftCell_3 = facesVector.faces[faceID_3].connectivity.cl[0] - 1;
		int rightCell_3 = facesVector.faces[faceID_3].connectivity.cr[0] - 1;

		int faceID_4 = cellsVector.cells[i].connectivity.faceIDs[3] - 1;
		int leftCell_4 = facesVector.faces[faceID_4].connectivity.cl[0] - 1;
		int rightCell_4 = facesVector.faces[faceID_4].connectivity.cr[0] - 1;

		if (x == cellsVector.cells[i].left && y == cellsVector.cells[i].bottom)	// Bottom left node
		{
			cellsVector.cells[i].bottomCellID = leftCell_1 + rightCell_1 - i;
			cellsVector.cells[i].rightCellID = leftCell_2 + rightCell_2 - i;
			cellsVector.cells[i].topCellID = leftCell_3 + rightCell_3 - i;
			cellsVector.cells[i].leftCellID = leftCell_4 + rightCell_4 - i;
		}
		else if (x == cellsVector.cells[i].right && y == cellsVector.cells[i].bottom)	// Bottom right node
		{
			cellsVector.cells[i].rightCellID = leftCell_1 + rightCell_1 - i;
			cellsVector.cells[i].topCellID = leftCell_2 + rightCell_2 - i;
			cellsVector.cells[i].leftCellID = leftCell_3 + rightCell_3 - i;
			cellsVector.cells[i].bottomCellID = leftCell_4 + rightCell_4 - i;
		}
		else if (x == cellsVector.cells[i].right && y == cellsVector.cells[i].top) // Top right node
		{
			cellsVector.cells[i].topCellID = leftCell_1 + rightCell_1 - i;
			cellsVector.cells[i].leftCellID = leftCell_2 + rightCell_2 - i;
			cellsVector.cells[i].bottomCellID = leftCell_3 + rightCell_3 - i;
			cellsVector.cells[i].rightCellID = leftCell_4 + rightCell_4 - i;
		}
		else if (x == cellsVector.cells[i].left && y == cellsVector.cells[i].top)	// Top left node
		{
			cellsVector.cells[i].leftCellID = leftCell_1 + rightCell_1 - i;
			cellsVector.cells[i].bottomCellID = leftCell_2 + rightCell_2 - i;
			cellsVector.cells[i].rightCellID = leftCell_3 + rightCell_3 - i;
			cellsVector.cells[i].topCellID = leftCell_4 + rightCell_4 - i;
		}
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
