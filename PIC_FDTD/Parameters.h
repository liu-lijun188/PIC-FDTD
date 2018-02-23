//! \file
//! \brief Definition of Parameters class 
//! \author Rahul Kalampattel
//! \date Last updated February 2018

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
	// Data members
	std::vector<std::string> valuesVector;	//!< Raw strings from input file	
	std::string meshFilePath;				//!< Path of mesh file
	std::string meshFile = "processedMesh";	//!< Name of processed mesh file

	bool fileNotOpened = false;				//!< Check if log file is open 
	bool firstLog = true;					//!< Check if this is the first log entry
	clock_t initialTime;					//!< Global simulation time

public:
	// Data members
	double timeStep;						//!< Time step
	int maximumNumberOfIterations;			//!< Maximum number of iterations
	int numberOfPatches;					//!< Number of patches
	int particlesPerCell;					//!< Particles per cell

	double charge;							//!< Particle charge
	double mass;							//!< Particle mass

	int maxSolverIterations;				//!< Maximum number of iterations for solver
	double residualTolerance;				//!< Tolerance for solver residuals
	double SORparameter;					//!< Successive over-relaxation parameter

	double epsilon0;						//!< Permittivity of free space (assumes vacuum)

	double xTest, yTest, uTest, vTest;		//!< Test parameter	
	int numCellsWithParticles;				//!< Test parameter	

	GridBasicInfo gridinfo;					//!< Basic grid properties
	GridGeo gridgeo;						//!< Detailed grid info


	// Constructor/destructor
	Parameters();							//!< Default constructor
	Parameters(std::string filename);		//!< Constructor
	~Parameters();							//!< Destructor


	// Methods
	void printValuesVector();				//!< Print raw input from valuesVector
	void assignInputs();					//!< Assign values to data members
	void printDataMembers();				//!< Print data members
	void processMesh();						//!< Process mesh file
	void hitReturnToEnter();				//!< Keeps console window open
	void logMessages(std::string message, 
		std::string filename, int line);	//!< Log messages and warnings
};