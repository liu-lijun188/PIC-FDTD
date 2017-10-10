//! \file
//! \brief Definition of Mesh class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#pragma once

#include "Parameters.h"

//! \class Mesh
//! \brief Definition
class Mesh
{
public:
	Mesh();										//!< Default constructor
	Mesh(Parameters *localParametersList);		//!< Constructor
	~Mesh();									//!< Destructor
	void checkMesh();							//!< Checks the mesh

	Parameters localParametersList;				
};