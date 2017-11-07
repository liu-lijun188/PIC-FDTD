//! \file
//! \brief Definition of Faces class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#pragma once

#include "GRID\face.hpp"

//! \class Faces
//! \brief Definition
class Faces : public FaceBase
{
public:
	Faces();					//!< Default constructor
	Faces(FaceBase baseFace);	//!< Constructor
	~Faces();					//!< Destructor
};