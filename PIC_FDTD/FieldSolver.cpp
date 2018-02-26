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
	// Set potential and fields at all nodes to zero at the start of each step
	mesh->nodesVector.clearPhi();
	mesh->nodesVector.clearFields();

	double h = mesh->h;

	// Gauss-Seidel solver with successive over-relaxation (SOR)
	// TODO: Enable switch statements to change solver type (GS-SOR, FFT, etc.)
	for (int i = 0; i < parametersList->maxSolverIterations; i++)
	{
		for (int j = 0; j < mesh->numNodes; j++)
		{
			// Periodic BCs in the x direction mean that L and R boundaries are
			// treated separately, while for T/B boundaries and the four corner
			// nodes, a three point stencil is used

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
			else if (mesh->nodesVector.nodes[j].boundaryType == "L")
			{
				mesh->nodesVector.nodes[j].phi = parametersList->SORparameter * 0.25 *
					((mesh->nodesVector.nodes[j].rho / parametersList->epsilon0) * h * h +
						mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].periodicXNodeID - 1].phi +
						mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].rightNodeID - 1].phi +
						mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].topNodeID - 1].phi +
						mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].bottomNodeID - 1].phi) +
						(1 - parametersList->SORparameter) * mesh->nodesVector.nodes[j].phi;
			}
			else if (mesh->nodesVector.nodes[j].boundaryType == "R")
			{
				mesh->nodesVector.nodes[j].phi = parametersList->SORparameter * 0.25 *
					((mesh->nodesVector.nodes[j].rho / parametersList->epsilon0) * h * h +
						mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].leftNodeID - 1].phi +
						mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].periodicXNodeID - 1].phi +
						mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].topNodeID - 1].phi +
						mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].bottomNodeID - 1].phi) +
						(1 - parametersList->SORparameter) * mesh->nodesVector.nodes[j].phi;
			}
			else if (mesh->nodesVector.nodes[j].boundaryType == "T" ||
				mesh->nodesVector.nodes[j].boundaryType == "B")
			{
				//mesh->nodesVector.nodes[j].phi = parametersList->SORparameter * 0.5 *
				//	((mesh->nodesVector.nodes[j].rho / parametersList->epsilon0) * h * h +
				//		mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].leftNodeID - 1].phi +
				//		mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].rightNodeID - 1].phi) +
				//		(1 - parametersList->SORparameter) * mesh->nodesVector.nodes[j].phi;

				// Dirichlet boundary condition of phi = 0 on top and bottom
				mesh->nodesVector.nodes[j].phi = 0;
			}
			else if (mesh->nodesVector.nodes[j].boundaryType == "TL" ||
					 mesh->nodesVector.nodes[j].boundaryType == "BL" )
			{
				//mesh->nodesVector.nodes[j].phi = parametersList->SORparameter * 0.5 *
				//	((mesh->nodesVector.nodes[j].rho / parametersList->epsilon0) * h * h +
				//		mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].periodicXNodeID - 1].phi +
				//		mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].rightNodeID - 1].phi) +
				//		(1 - parametersList->SORparameter) * mesh->nodesVector.nodes[j].phi;

				// Dirichlet boundary condition of phi = 0 on top and bottom
				mesh->nodesVector.nodes[j].phi = 0;
			}
			else if (mesh->nodesVector.nodes[j].boundaryType == "TR" ||
					 mesh->nodesVector.nodes[j].boundaryType == "BR")
			{
				//mesh->nodesVector.nodes[j].phi = parametersList->SORparameter * 0.5 *
				//	((mesh->nodesVector.nodes[j].rho / parametersList->epsilon0) * h * h +
				//		mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].leftNodeID - 1].phi +
				//		mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].periodicXNodeID - 1].phi) +
				//		(1 - parametersList->SORparameter) * mesh->nodesVector.nodes[j].phi;

				// Dirichlet boundary condition of phi = 0 on top and bottom
				mesh->nodesVector.nodes[j].phi = 0;
			}
		}

		// Check convergence
		if (i != 0 && i % 9 == 0)
		{
			double residualSum = 0;

			for (int j = 0; j < mesh->numNodes; j++)
			{
				// TODO: Include other nodes in calculating residual sum (???)
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

		// Account for periodic BCs in x direction
		for (int i = 0; i < mesh->numNodes; i++)
		{
			if (mesh->nodesVector.nodes[i].boundaryType == "TL" ||
				mesh->nodesVector.nodes[i].boundaryType == "L" ||
				mesh->nodesVector.nodes[i].boundaryType == "BL")
			{
				mesh->nodesVector.nodes[i].phi = 0.5 * (mesh->nodesVector.nodes[i].phi +
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].periodicXNodeID - 1].phi);
				mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].periodicXNodeID - 1].phi =
					mesh->nodesVector.nodes[i].phi;
			}
		}
	}

	// Electric field
	for (int i = 0; i < mesh->numNodes; i++)
	{
		if (mesh->nodesVector.nodes[i].boundaryType == "internal")
		{
			mesh->nodesVector.nodes[i].fields[0] = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].leftNodeID - 1].phi -
				mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].rightNodeID - 1].phi) / (2 * h);

			mesh->nodesVector.nodes[i].fields[1] = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].bottomNodeID - 1].phi -
				mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].topNodeID - 1].phi) / (2 * h);
		}
		else if (mesh->nodesVector.nodes[i].boundaryType == "T")
		{
			mesh->nodesVector.nodes[i].fields[0] = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].leftNodeID - 1].phi -
				mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].rightNodeID - 1].phi) / (2 * h);

			mesh->nodesVector.nodes[i].fields[1] = (mesh->nodesVector.nodes[i].phi - 
				mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].bottomNodeID - 1].phi) / h;
		}
		else if (mesh->nodesVector.nodes[i].boundaryType == "B")
		{
			mesh->nodesVector.nodes[i].fields[0] = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].leftNodeID - 1].phi -
				mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].rightNodeID - 1].phi) / (2 * h);

			mesh->nodesVector.nodes[i].fields[1] = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].topNodeID - 1].phi -
				mesh->nodesVector.nodes[i].phi) / h;
		}
		else if (mesh->nodesVector.nodes[i].boundaryType == "L")
		{
			mesh->nodesVector.nodes[i].fields[0] = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].periodicXNodeID - 1].phi -
				mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].rightNodeID - 1].phi) / (2 * h);

			mesh->nodesVector.nodes[i].fields[1] = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].bottomNodeID - 1].phi -
				mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].topNodeID - 1].phi) / (2 * h);
		}
		else if (mesh->nodesVector.nodes[i].boundaryType == "R")
		{
			mesh->nodesVector.nodes[i].fields[0] = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].leftNodeID - 1].phi -
				mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].periodicXNodeID - 1].phi) / (2 * h);

			mesh->nodesVector.nodes[i].fields[1] = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].bottomNodeID - 1].phi -
				mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].topNodeID - 1].phi) / (2 * h);
		}
		else if (mesh->nodesVector.nodes[i].boundaryType == "TL")
		{
			mesh->nodesVector.nodes[i].fields[0] = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].periodicXNodeID - 1].phi -
				mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].rightNodeID - 1].phi) / (2 * h);

			mesh->nodesVector.nodes[i].fields[1] = (mesh->nodesVector.nodes[i].phi -
				mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].bottomNodeID - 1].phi) / h;
		}
		else if (mesh->nodesVector.nodes[i].boundaryType == "BL")
		{
			mesh->nodesVector.nodes[i].fields[0] = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].periodicXNodeID - 1].phi -
				mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].rightNodeID - 1].phi) / (2 * h);

			mesh->nodesVector.nodes[i].fields[1] = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].topNodeID - 1].phi -
				mesh->nodesVector.nodes[i].phi) / h;
		}
		else if (mesh->nodesVector.nodes[i].boundaryType == "TR")
		{
			mesh->nodesVector.nodes[i].fields[0] = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].leftNodeID - 1].phi -
				mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].periodicXNodeID - 1].phi) / (2 * h);

			mesh->nodesVector.nodes[i].fields[1] = (mesh->nodesVector.nodes[i].phi -
				mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].bottomNodeID - 1].phi) / h;
		}
		else if (mesh->nodesVector.nodes[i].boundaryType == "BR")
		{
			mesh->nodesVector.nodes[i].fields[0] = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].leftNodeID - 1].phi -
				mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].periodicXNodeID - 1].phi) / (2 * h);

			mesh->nodesVector.nodes[i].fields[1] = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].topNodeID - 1].phi -
				mesh->nodesVector.nodes[i].phi) / h;
		}
	}
}

// Destructor
FieldSolver::~FieldSolver()
{
}