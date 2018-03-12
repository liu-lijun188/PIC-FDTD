//! \file
//! \brief Definition of Parameters class 
//! \author Rahul Kalampattel
//! \date Last updated March 2018

#pragma once

#include <chrono>
#include <ctime>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "GRID/grid.hpp"

#include "omp.h"

//! \class Parameters 
//! \brief Handles pre-processing of input parameters
class Parameters
{
private:
	// Data members
	std::vector<std::string> valuesVector;	//!< Raw strings from input file	
	std::string meshFilePath;				//!< Path of mesh file
	std::string meshFile = "processedMesh";	//!< Name of processed mesh file

	bool fileNotOpened = false;				//!< Check if input file was opened 
	bool firstLog = true;					//!< Check if this is the first log entry
	std::chrono::system_clock::time_point initialTime;	//!< Global simulation time

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
	double xPerturbation, yPerturbation;	//!< Test parameter
	int numCellsWithParticles;				//!< Test parameter	
	int plotFrequency;						//!< Test parameter
	double meshScalingParameter;			//!< Test parameter
	std::string solverType;					//!< Test parameter
	std::string xBCType, yBCType;			//!< Test parameter
	double xBCValue, yBCValue;				//!< Test parameter
	int twoStream;							//!< Test parameter
	int axisymmetric;						//!< Test parameter
	int numThreads;						//!< Test parameter

	int numErrors = 0;						//!< Number of errors detected during simulation

	GridBasicInfo gridinfo;					//!< Basic grid properties
	GridGeo gridgeo;						//!< Detailed grid info


	// Constructor/destructor
	Parameters();							//!< Default constructor
	Parameters(std::string filename);		//!< Constructor
	~Parameters();							//!< Destructor


	// Methods
	void assignInputs();					//!< Assign values to data members
	void processMesh();						//!< Process mesh file
	void logMessages(std::string message, std::string filename, 
		int line, int messageType);			//!< Log messages, warnings and errors
	void logBrief(std::string message, 
		int messageType);					//!< Log brief messages
};