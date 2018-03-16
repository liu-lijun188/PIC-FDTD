//! \file
//! \brief Implementation of FDTD class 
//! \author Rahul Kalampattel
//! \date Last updated March 2018

#include "FDTD.h"

// Default constructor
FDTD::FDTD()
{
}


// Constructor
FDTD::FDTD(Parameters *parametersList, Mesh *mesh)
{
	// TODO: Based on the geometry of the existing mesh, generate a new mesh
	// with a finer grid spacing. Nodes in every second row and second column are 
	// used to calculate E field parameters, while the alternate nodes are used
	// for B field parameters. Alternatively, generate two separate meshes with 
	// the appropriate coordinates to create a Yee mesh when put together.
	
	// TODO: Solve Maxwell's equations to find the E field based on B, and the
	// B field based on E. Both sets of calculations are time-shifted using the 
	// leapfrog method. The effects of any source terms are also accounted for
	// in between.

	// TODO: Interpolate results back from the fine FDTD mesh to the coarse PIC
	// mesh, either through the use of lookup tables (inefficient), shape functions,
	// or some other methods.
}


// Destructor
FDTD::~FDTD()
{
}