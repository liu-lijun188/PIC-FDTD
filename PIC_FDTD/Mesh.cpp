//! \file
//! \brief Implementation of Mesh class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#include "Mesh.h"

Mesh::Mesh()
{
}


Mesh::Mesh(Parameters *localParametersList)
{
	this->localParametersList = *localParametersList;
}


Mesh::~Mesh()
{
}