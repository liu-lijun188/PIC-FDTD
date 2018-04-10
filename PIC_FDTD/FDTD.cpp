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

	// TODO: Interpolate relevant quantities from the coarse PIC mesh to the 
	// fine FDTD mesh (plus in reverse).
	// 1. The use of shape functions on a 2D quad mesh is identical to using bilinear
	// (2D) interpolation, as currently done in the FieldInterpolator class 
	// 2. In order to achieve this, each node of the FDTD mesh needs to be mapped 
	// to a cell of the PIC mesh 
	// 3. After this link is identified, interpolation of quantities is simple
	
	for (int i = 0; i < FDTDmesh.numNodes; i++)
	{
		// TODO: Identify which node goes in which cell
		FDTDmesh.nodesVector.nodes[i].PICcellID = i + 1;
	}

	// TODO: Solve Maxwell's equations to find the E field based on B, and the
	// B field based on E. Both sets of calculations are time-shifted using the 
	// leapfrog method. The effects of any source terms are also accounted for
	// in between.
}


// Destructor
FDTD::~FDTD()
{
}