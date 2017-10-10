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

using namespace std;

//! \class Parameters 
//! \brief Handles pre-processing of input parameters
class Parameters
{
private:
	vector<string> valuesVector;
	bool fileNotOpened = false;
	bool firstLog = true;
	clock_t initialTime, currentTime;

public:
	Parameters();						//!< Default constructor
	Parameters(string filename);		//!< Constructor
	~Parameters();						//!< Destructor

	void printValuesVector();			//!< Print raw input from valuesVector
	void distributeInputs();			//!< Assign values to member variables
	void printMemberVariables();		//!< Print member variables
	void hitReturnToEnter();			//!< Keeps console window open
	void logMessages(string message);	//!< Log error messages

	double timeStep;				
	int maximumNumberOfIterations, numberOfPatches, particlesPerPatch;
	string meshFilePath;
	string processedMesh = "processedMesh";
	GridBasicInfo gridinfo;
	GridGeo gridgeo;
};