//! \file
//! \brief Definition of Patch class 
//! \author Rahul Kalampattel
//! \date Last updated March 2018

#pragma once

#include <iostream>

#include "ChargeProjector.h"
#include "FDTD.h"
#include "FieldInterpolator.h"
#include "FieldSolver.h"
#include "MCC.h"
#include "Mesh.h"
#include "Parameters.h"
#include "ParticlePusher.h"
#include "VectorParticle.h"

//! \class Patch
//! \brief Handles all aspects of an instance of the simulation
class Patch
{
private:
	// Data members
	double time;										//!< Local simulation time
	Parameters parametersList;							//!< Copy of parameters list
	Mesh mesh;											//!< Details of mesh
	VectorParticle particlesVector;						//!< Vector of resident particles


	// Methods
	void generateParticleOutput(vector2D data, 
		int numParticles, double time);					//!< Generate Tecplot output for particles
	void generateNodeOutput(Mesh mesh, double time);	//!< Generate Tecplot output for nodes
	void Patch::generateGlobalOutput(double EK,
		double EP, int N, double time);					//!< Generate Tecplot output for global parameters

public:
	// Data members
	int patchID;										//!< Patch ID
	int numErrors;										//!< Public copy of numErrors from parametersList


	// Constructor/destructor
	Patch();											//!< Default constructor
	Patch(Parameters *parametersList, int patchID);		//!< Constructor
	~Patch();											//!< Destructor


	// Methods
	void startPIC();									//!< Start the PIC loop within a Patch object	
};