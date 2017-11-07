//! \file
//! \brief Implementation of Ghost class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#include "Ghost.h"

// Default constructor
Ghost::Ghost()
{
}

// Constructor
Ghost::Ghost(CellBase baseCell)
{
	this->connectivity = baseCell.connectivity;
	this->geometry = baseCell.geometry;
}

// Destructor
Ghost::~Ghost()
{
}