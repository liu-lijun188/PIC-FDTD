//! \file
//! \brief Implementation of VectorGhost class 
//! \author Rahul Kalampattel
//! \date Last updated November 2017

#include "VectorGhost.h"

// Default constructor
VectorGhost::VectorGhost()
{
}


// Destructor
VectorGhost::~VectorGhost()
{
}


// Allocate CellBase elements to ghosts data member
void VectorGhost::allocate(std::vector<CellBase> cells)
{
	for (int i = 0; i < cells.size(); i++)
	{
		Ghost tempGhost(cells[i]);
		this->ghosts.push_back(tempGhost);
	}
}
