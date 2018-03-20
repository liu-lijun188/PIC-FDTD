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
#include <random>
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
	std::string meshFile = "processedMesh";	//!< Name of processed mesh file

	bool fileNotOpened = false;				//!< Check if input file was opened 
	bool firstLog = true;					//!< Check if this is the first log entry
	std::chrono::system_clock::time_point initialTime;	//!< Global simulation time

public:
	// Data members
	int numErrors = 0;						//!< Number of errors detected during simulation
	GridBasicInfo gridinfo;					//!< Basic grid properties
	GridGeo gridgeo;						//!< Detailed grid info

	// Constants
	double epsilon0;						//!< Permittivity of free space (assumes vacuum?)

	// Simulation parameters
	double timeStep;						//!< Time step
	int maximumNumberOfIterations;			//!< Maximum number of iterations
	int numberOfPatches;					//!< Number of patches
	int particlesPerCell;					//!< Particles per cell
	int numCellsWithParticles;				//!< Number of cells in which particles are seeded	
	std::string simulationType;				//!< Simulation type (full, partial or electron)
	std::string propellant;					//!< Propellant used in simulation (xenon)
	bool axisymmetric;						//!< True if axisymmetric simulation is required
	bool twoStream;							//!< True is two-stream problem is bring modelled

	// Particle parameters
	double xInitial;						//!< Initial particle x position
	double yInitial;						//!< Initial particle y position
	double uInitial;						//!< Initial particle x velocity
	double vInitial;						//!< Initial particle y velocity
	double xPerturbation;					//!< Maximum random deviation from initial position
	double yPerturbation;					//!< Maximum random deviation from initial position

	// Field parameters
	double xEfield;							//!< External x electric field
	double yEfield;							//!< External y electric field
	double zBfield;							//!< External z magnetic field
	double FDTDtimeStep;					//!< Time step for FDTD solver

	// Mesh parameters
	std::string meshFilePath;				//!< Path of mesh file
	double meshScalingParameter;			//!< Mesh scaling parameter

	// Solver parameters
	std::string solverType;					//!< Solver type (GS, FFT)
	int maxSolverIterations;				//!< Maximum number of iterations for solver
	double residualTolerance;				//!< Tolerance for solver residuals
	double SORparameter;					//!< Successive over-relaxation parameter
	std::string xBCType;					//!< Boundary condition in x direction (periodic, open, dirichlet, neumann)
	std::string yBCType;					//!< Boundary condition in y direction (periodic, open, dirichlet, neumann)
	double xBCValue;						//!< Value of x boundary condition
	double yBCValue;						//!< Value of y boundary condition

	// Parallelisation parameters
	int numThreads;							//!< Number of OpenMP threads for parallelisation
	
	// Output parameters
	int plotFrequency;						//!< Iterations between plots
	std::string tecplotMesh;				//!< Tecplot output mesh file
	std::string tecplotParticleSolution;	//!< Tecplot particle solution file
	std::string tecplotNodeSolution;		//!< Tecplot node solution file
	std::string tecplotGlobalSolution;		//!< Tecplot global solution file


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