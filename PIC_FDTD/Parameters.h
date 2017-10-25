//! \file
//! \brief Definition of Parameters class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#pragma once

#include <ctime>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "GRID/grid.hpp"
#include "VectorCell.h"
#include "VectorFace.h"
#include "VectorGhost.h"
#include "VectorNode.h"

//! \class Parameters 
//! \brief Handles pre-processing of input parameters
class Parameters
{
private:
	std::vector<std::string> valuesVector;
	bool fileNotOpened = false;
	bool firstLog = true;
	clock_t initialTime;

	std::string processedMesh = "processedMesh";
	GridBasicInfo gridinfo;
	GridGeo gridgeo;

public:
	Parameters();						//!< Default constructor
	Parameters(std::string filename);		//!< Constructor
	~Parameters();						//!< Destructor

	void printValuesVector();			//!< Print raw input from valuesVector
	void assignInputs();				//!< Assign values to member variables
	void printMemberVariables();		//!< Print member variables
	void processMesh();					//!< Process mesh file
	void hitReturnToEnter();			//!< Keeps console window open
	void logMessages(std::string message);	//!< Log messages and warnings

	double timeStep;				
	int maximumNumberOfIterations, numberOfPatches, particlesPerPatch;
	std::string meshFilePath;

	VectorCell localCellsVector;
	VectorFace localFacesVector;
	VectorGhost localGhostVector;
	VectorNode localNodesVector;

};