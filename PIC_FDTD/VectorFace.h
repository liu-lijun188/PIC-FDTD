//! \file
//! \brief Definition of VectorFace class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#pragma once

#include "Faces.h"

//! \class VectorFace
//! \brief Definition
class VectorFace
{
public:
	VectorFace();	//!< Default constructor
	~VectorFace();	//!< Destructor
	void allocate(std::vector<FaceBase> faces);	//!< Allocate faces to faces attribute

	std::vector<Faces> faces;
};