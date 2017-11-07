//! \file
//! \brief Implementation of Mesh class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#include "Mesh.h"

// Default constructor
Mesh::Mesh()
{
}

// Constructor
Mesh::Mesh(Parameters *localParametersList)
{
	this->localParametersList = *localParametersList;
}

// Destructor
Mesh::~Mesh()
{
}