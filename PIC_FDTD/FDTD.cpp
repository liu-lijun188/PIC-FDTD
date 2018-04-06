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
	parametersList->processMesh("FDTD");
	FDTDmesh = Mesh(parametersList, "FDTD");

	// TODO: Interpolate relevant quantities from the coarse PIC mesh to the 
	// fine FDTD mesh (plus in reverse), either through the use of lookup tables 
	// (inefficient), shape functions, or some other methods.

	// TODO: Solve Maxwell's equations to find the E field based on B, and the
	// B field based on E. Both sets of calculations are time-shifted using the 
	// leapfrog method. The effects of any source terms are also accounted for
	// in between.
}


// Destructor
FDTD::~FDTD()
{
}