//! \file
//! \brief Definition of VectorGhost class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#pragma once

#include "Ghost.h"

//! \class VectorGhost
//! \brief Definition
class VectorGhost
{
public:
	VectorGhost();	//!< Default constructor
	~VectorGhost();	//!< Destructor

	vector<Ghost> ghostVector;
};