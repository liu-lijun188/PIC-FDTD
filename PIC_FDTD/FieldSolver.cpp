//! \file
//! \brief Implementation of FieldSolver class 
//! \author Rahul Kalampattel
//! \date Last updated February 2018

#include "FieldSolver.h"

// Default constructor
FieldSolver::FieldSolver()
{
}

// Constructor
FieldSolver::FieldSolver(Parameters *parametersList, Mesh *mesh, VectorParticle *particlesVector)
{
	// Set potential at all nodes to zero at the start of each step
	// TODO: Could make this a method of VectorNode in future
	for (int i = 0; i < mesh->numNodes; i++)
	{
		mesh->nodesVector.nodes[i].phi = 0;
	}

	// TODO: Make this a property of mesh and access it from there
	double h = 0.02;

	// Gauss-Seidel solver with successive over-relaxation (SOR)
	// TODO: Enable switch statements to change solver type (GS-SOR, FFT, etc.)
	for (int i = 0; i < parametersList->maxSolverIterations; i++)
	{
		for (int j = 0; j < mesh->numNodes; j++)
		{
			if (mesh->nodesVector.nodes[j].boundaryType == "internal")
			{
				mesh->nodesVector.nodes[j].phi = parametersList->SORparameter * 0.25 *
					((mesh->nodesVector.nodes[j].rho / parametersList->epsilon0) * h * h +
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].leftNodeID - 1].phi +
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].rightNodeID - 1].phi +
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].topNodeID - 1].phi +
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].bottomNodeID - 1].phi) + 
					(1 - parametersList->SORparameter) * mesh->nodesVector.nodes[j].phi;
			}
		}

		// Check convergence
		if (i % 9 == 0)
		{
			double residualSum = 0;

			for (int j = 0; j < mesh->numNodes; j++)
			{

				if (mesh->nodesVector.nodes[j].boundaryType == "internal")
				{
					double residual =
						(mesh->nodesVector.nodes[j].rho / parametersList->epsilon0) * h * h +
						mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].leftNodeID - 1].phi +
						mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].rightNodeID - 1].phi +
						mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].topNodeID - 1].phi +
						mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].bottomNodeID - 1].phi -
						4 * mesh->nodesVector.nodes[j].phi;

					residualSum += residual * residual;
				}
			}
			
			if (sqrt(residualSum / static_cast<double>(mesh->numNodes)) < parametersList->residualTolerance)
			{
				break; 
			}
		}
	}

	// Electric field
	for (int i = 0; i < mesh->numNodes; i++)
	{
		if (mesh->nodesVector.nodes[i].boundaryType == "internal")
		{
			mesh->nodesVector.nodes[i].Ex = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].leftNodeID - 1].phi -
				mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].rightNodeID - 1].phi) / (2 * h);

			mesh->nodesVector.nodes[i].Ey = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].bottomNodeID - 1].phi -
				mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].topNodeID - 1].phi) / (2 * h);
		}
	}
}

// Destructor
FieldSolver::~FieldSolver()
{
}