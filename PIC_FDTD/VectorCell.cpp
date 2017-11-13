//! \file
//! \brief Implementation of VectorCell class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#include "VectorCell.h"

// Default constructor
VectorCell::VectorCell()
{
}

// Destructor
VectorCell::~VectorCell()
{
}

// Allocate cells to cells attribute
void VectorCell::allocate(std::vector<CellBase> cells)
{
	for (int i = 0; i < cells.size(); i++)
	{
		Cells tempCell(cells[i]);
		this->cells.push_back(tempCell);
	}
}