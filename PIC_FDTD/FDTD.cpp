//! \file
//! \brief Implementation of FDTD class 
//! \author Rahul Kalampattel
//! \date Last updated April 2018

#include "FDTD.h"

// Default constructor
FDTD::FDTD()
{
}


// Constructor
FDTD::FDTD(Parameters *parametersList, Mesh *mesh)
{
	// Based on the geometry of the existing mesh, generate a new mesh with a 
	// finer grid spacing. Nodes in every second row and second column are used 
	// to calculate E field parameters, while the alternate nodes are used for 
	// B field parameters (i.e a Yee mesh). 
	// TODO: Don't need to regenerate FDTD mesh every single class instance?
	parametersList->processMesh("FDTD");
	FDTDmesh = Mesh(parametersList, "FDTD");
	
	// Map nodes of the FDTD mesh to cells of the PIC mesh 	
	// TODO: Check that the FDTD mesh spacing divides the PIC mesh spacing evenly,
	// e.g. 0.1 and 0.2 work (step == 2), but 0.15 and 0.2 don't (step == 1.333).
	int currentCol = 0, cellShift = 0;
	int step = static_cast<int>(round(mesh->h / FDTDmesh.h));
	for (int i = 0; i < FDTDmesh.numNodes; i += (FDTDmesh.numRows + 1))
	{
		int currentRow = 1;
		if (currentCol == step + 1)
		{
			cellShift += mesh->numRows;
			currentCol = 1;
		}
		int currentCell = 1 + cellShift;

		FDTDmesh.nodesVector.nodes[i].PICcellID = currentCell;

		int j = 1;
		while (currentRow < FDTDmesh.numRows + 1)
		{
			for (int k = 1; k <= step; k++)
			{
				FDTDmesh.nodesVector.nodes[i + j].PICcellID = currentCell;
				j++;
				currentRow++;
			}
			currentCell++;
		}
		currentCol++;
	}

	for (int i = 0; i < FDTDmesh.numNodes; i++)
	{
		// TODO: Can change all of the below to references to avoid copying large 
		// amounts of data for each calculation

		int cellID = FDTDmesh.nodesVector.nodes[i].PICcellID - 1;
		int nodeID_0 = mesh->cellsVector.cells[cellID].connectivity.nodeIDs[0] - 1;
		int nodeID_1 = mesh->cellsVector.cells[cellID].connectivity.nodeIDs[1] - 1;
		int nodeID_2 = mesh->cellsVector.cells[cellID].connectivity.nodeIDs[2] - 1;
		int nodeID_3 = mesh->cellsVector.cells[cellID].connectivity.nodeIDs[3] - 1;

		double left = mesh->cellsVector.cells[cellID].left;
		double right = mesh->cellsVector.cells[cellID].right;
		double top = mesh->cellsVector.cells[cellID].top;
		double bottom = mesh->cellsVector.cells[cellID].bottom;

		double hSquared = mesh->h * mesh->h;

		double x1 = FDTDmesh.nodesVector.nodes[i].geometry.X.element(0, 0);
		double x2 = FDTDmesh.nodesVector.nodes[i].geometry.X.element(1, 0);

		std::string firstNodePosition = mesh->cellsVector.cells[cellID].firstNodePosition;

		// TODO: Interpolate all relevant quantities from PIC to FDTD mesh 
		if (firstNodePosition == "TL")
		{
			for (int j = 0; j < 6; j++)
			{
				FDTDmesh.nodesVector.nodes[i].EMfield[j] =
					mesh->nodesVector.nodes[nodeID_0].EMfield[j] * (right - x1) * (x2 - bottom) / hSquared +
					mesh->nodesVector.nodes[nodeID_1].EMfield[j] * (right - x1) * (top - x2) / hSquared +
					mesh->nodesVector.nodes[nodeID_2].EMfield[j] * (x1 - left) * (top - x2) / hSquared +
					mesh->nodesVector.nodes[nodeID_3].EMfield[j] * (x1 - left) * (x2 - bottom) / hSquared;
			}
		}
		else if (firstNodePosition == "BL")
		{
			for (int j = 0; j < 6; j++)
			{
				FDTDmesh.nodesVector.nodes[i].EMfield[j] =
					mesh->nodesVector.nodes[nodeID_0].EMfield[j] * (right - x1) * (top - x2) / hSquared +
					mesh->nodesVector.nodes[nodeID_1].EMfield[j] * (x1 - left) * (top - x2) / hSquared +
					mesh->nodesVector.nodes[nodeID_2].EMfield[j] * (x1 - left) * (x2 - bottom) / hSquared +
					mesh->nodesVector.nodes[nodeID_3].EMfield[j] * (right - x1) * (x2 - bottom) / hSquared;
			}
		}
		else if (firstNodePosition == "BR")
		{
			for (int j = 0; j < 6; j++)
			{
				FDTDmesh.nodesVector.nodes[i].EMfield[j] =
					mesh->nodesVector.nodes[nodeID_0].EMfield[j] * (x1 - left) * (top - x2) / hSquared +
					mesh->nodesVector.nodes[nodeID_1].EMfield[j] * (x1 - left) * (x2 - bottom) / hSquared +
					mesh->nodesVector.nodes[nodeID_2].EMfield[j] * (right - x1) * (x2 - bottom) / hSquared +
					mesh->nodesVector.nodes[nodeID_3].EMfield[j] * (right - x1) * (top - x2) / hSquared;
			}
		}
		else if (firstNodePosition == "TR")
		{
			for (int j = 0; j < 6; j++)
			{
				FDTDmesh.nodesVector.nodes[i].EMfield[j] =
					mesh->nodesVector.nodes[nodeID_0].EMfield[j] * (x1 - left) * (x2 - bottom) / hSquared +
					mesh->nodesVector.nodes[nodeID_1].EMfield[j] * (right - x1) * (x2 - bottom) / hSquared +
					mesh->nodesVector.nodes[nodeID_2].EMfield[j] * (right - x1) * (top - x2) / hSquared +
					mesh->nodesVector.nodes[nodeID_3].EMfield[j] * (x1 - left) * (top - x2) / hSquared;
			}
		}
	}

	// TODO: Solve Maxwell's equations to find the E field based on B, and the
	// B field based on E. Both sets of calculations are time-shifted using the 
	// leapfrog method. The effects of any source terms are also accounted for
	// in between.

	// TODO: Interpolate all relevant quantities from FDTD to PIC mesh (reverse 
	// of the above process).

	parametersList->logBrief("FDTD solver exited", 1);
}


// Destructor
FDTD::~FDTD()
{
}