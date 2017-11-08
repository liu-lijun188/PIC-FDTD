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

//! \class Parameters 
//! \brief Handles pre-processing of input parameters
class Parameters
{
private:
	std::vector<std::string> valuesVector;
	bool fileNotOpened = false;
	bool firstLog = true;
	clock_t initialTime;

	std::string meshFilePath;
	std::string processedMeshFile = "processedMesh";

	std::string tecplotMesh = "tecplotMeshC";
	std::string tecplotSolution = "tecplotSolutionC";

public:
	Parameters();						//!< Default constructor
	Parameters(std::string filename);	//!< Constructor
	~Parameters();						//!< Destructor

	void printValuesVector();					//!< Print raw input from valuesVector
	void assignInputs();						//!< Assign values to member variables
	void printMemberVariables();				//!< Print member variables
	void processMesh();							//!< Process mesh file
	void generateOutput(vector2D data, int N);	//!< Generate Tecplot output
	void hitReturnToEnter();					//!< Keeps console window open
	void logMessages(std::string message, 
		std::string filename, int line);		//!< Log messages and warnings

	double timeStep;				
	int maximumNumberOfIterations, numberOfPatches, particlesPerCell;

	GridBasicInfo gridinfo;
	GridGeo gridgeo;
};