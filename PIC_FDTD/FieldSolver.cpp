//! \file
//! \brief Implementation of FieldSolver class 
//! \author Rahul Kalampattel
//! \date Last updated March 2018

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
	for (int i = 0; i < parametersList->maxSolverIterations; i++)
	{
		if (parametersList->solverType == "GS")
		{
			for (int j = 0; j < mesh->numNodes; j++)
			{
				// Five point stencil is used on internal points and periodic
				// boundaries, while for other BCs and the four corner nodes, a
				// three point stencil or fixed value is used

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
					if (parametersList->xBC == "periodic")
					{
						mesh->nodesVector.nodes[j].phi = parametersList->SORparameter * 0.25 *
							((mesh->nodesVector.nodes[j].rho / parametersList->epsilon0) * h * h +
								mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].periodicXNodeID - 1].phi +
								mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].rightNodeID - 1].phi +
								mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].topNodeID - 1].phi +
								mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].bottomNodeID - 1].phi) +
								(1 - parametersList->SORparameter) * mesh->nodesVector.nodes[j].phi;
					}
					else
					{
						//mesh->nodesVector.nodes[j].phi = parametersList->SORparameter * 0.5 *
						//	((mesh->nodesVector.nodes[j].rho / parametersList->epsilon0) * h * h +
						//		mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].topNodeID - 1].phi +
						//		mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].bottomNodeID - 1].phi) +
						//		(1 - parametersList->SORparameter) * mesh->nodesVector.nodes[j].phi;

						// Dirichlet boundary condition of phi = 0 on left
						mesh->nodesVector.nodes[j].phi = 0;
					}

				}
				else if (mesh->nodesVector.nodes[j].boundaryType == "R")
				{
					if (parametersList->xBC == "periodic")
					{
						mesh->nodesVector.nodes[j].phi = parametersList->SORparameter * 0.25 *
							((mesh->nodesVector.nodes[j].rho / parametersList->epsilon0) * h * h +
								mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].leftNodeID - 1].phi +
								mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].periodicXNodeID - 1].phi +
								mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].topNodeID - 1].phi +
								mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].bottomNodeID - 1].phi) +
								(1 - parametersList->SORparameter) * mesh->nodesVector.nodes[j].phi;
					}
					else
					{
						//mesh->nodesVector.nodes[j].phi = parametersList->SORparameter * 0.5 *
						//	((mesh->nodesVector.nodes[j].rho / parametersList->epsilon0) * h * h +
						//		mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].topNodeID - 1].phi +
						//		mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].bottomNodeID - 1].phi) +
						//		(1 - parametersList->SORparameter) * mesh->nodesVector.nodes[j].phi;

						// Dirichlet boundary condition of phi = 0 on right
						mesh->nodesVector.nodes[j].phi = 0;
					}

				}
				else if (mesh->nodesVector.nodes[j].boundaryType == "T")
				{
					if (parametersList->yBC == "periodic")
					{
						mesh->nodesVector.nodes[j].phi = parametersList->SORparameter * 0.25 *
							((mesh->nodesVector.nodes[j].rho / parametersList->epsilon0) * h * h +
								mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].leftNodeID - 1].phi +
								mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].rightNodeID - 1].phi +
								mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].periodicYNodeID - 1].phi +
								mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].bottomNodeID - 1].phi) +
								(1 - parametersList->SORparameter) * mesh->nodesVector.nodes[j].phi;
					}
					else
					{
						//mesh->nodesVector.nodes[j].phi = parametersList->SORparameter * 0.5 *
						//	((mesh->nodesVector.nodes[j].rho / parametersList->epsilon0) * h * h +
						//		mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].leftNodeID - 1].phi +
						//		mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].rightNodeID - 1].phi) +
						//		(1 - parametersList->SORparameter) * mesh->nodesVector.nodes[j].phi;

						// Dirichlet boundary condition of phi = 0 on top 
						mesh->nodesVector.nodes[j].phi = 0;
					}
				}
				else if (mesh->nodesVector.nodes[j].boundaryType == "B")
				{
					if (parametersList->yBC == "periodic")
					{
						mesh->nodesVector.nodes[j].phi = parametersList->SORparameter * 0.25 *
							((mesh->nodesVector.nodes[j].rho / parametersList->epsilon0) * h * h +
								mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].leftNodeID - 1].phi +
								mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].rightNodeID - 1].phi +
								mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].topNodeID - 1].phi +
								mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].periodicYNodeID - 1].phi) +
								(1 - parametersList->SORparameter) * mesh->nodesVector.nodes[j].phi;
					}
					else
					{
						//mesh->nodesVector.nodes[j].phi = parametersList->SORparameter * 0.5 *
						//	((mesh->nodesVector.nodes[j].rho / parametersList->epsilon0) * h * h +
						//		mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].leftNodeID - 1].phi +
						//		mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].rightNodeID - 1].phi) +
						//		(1 - parametersList->SORparameter) * mesh->nodesVector.nodes[j].phi;

						// Dirichlet boundary condition of phi = 0 on bottom
						mesh->nodesVector.nodes[j].phi = 0;
					}
				}
				else 
				{
					if (parametersList->xBC == "periodic" &&
						parametersList->yBC == "periodic")
					{
						if (mesh->nodesVector.nodes[j].boundaryType == "TL")
						{
							mesh->nodesVector.nodes[j].phi = parametersList->SORparameter * 0.25 *
								((mesh->nodesVector.nodes[j].rho / parametersList->epsilon0) * h * h +
									mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].periodicXNodeID - 1].phi +
									mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].rightNodeID - 1].phi +
									mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].periodicYNodeID - 1].phi +
									mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].bottomNodeID - 1].phi) +
									(1 - parametersList->SORparameter) * mesh->nodesVector.nodes[j].phi;
						}
						else if (mesh->nodesVector.nodes[j].boundaryType == "BL")
						{
							mesh->nodesVector.nodes[j].phi = parametersList->SORparameter * 0.25 *
								((mesh->nodesVector.nodes[j].rho / parametersList->epsilon0) * h * h +
									mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].periodicXNodeID - 1].phi +
									mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].rightNodeID - 1].phi +
									mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].topNodeID - 1].phi +
									mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].periodicYNodeID - 1].phi) +
									(1 - parametersList->SORparameter) * mesh->nodesVector.nodes[j].phi;
						}
						else if (mesh->nodesVector.nodes[j].boundaryType == "TR")
						{
							mesh->nodesVector.nodes[j].phi = parametersList->SORparameter * 0.25 *
								((mesh->nodesVector.nodes[j].rho / parametersList->epsilon0) * h * h +
									mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].leftNodeID - 1].phi +
									mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].periodicXNodeID - 1].phi +
									mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].periodicYNodeID - 1].phi +
									mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].bottomNodeID - 1].phi) +
									(1 - parametersList->SORparameter) * mesh->nodesVector.nodes[j].phi;
						}
						else if (mesh->nodesVector.nodes[j].boundaryType == "BR")
						{
							mesh->nodesVector.nodes[j].phi = parametersList->SORparameter * 0.25 *
								((mesh->nodesVector.nodes[j].rho / parametersList->epsilon0) * h * h +
									mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].leftNodeID - 1].phi +
									mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].periodicXNodeID - 1].phi +
									mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].topNodeID - 1].phi +
									mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].periodicYNodeID - 1].phi) +
									(1 - parametersList->SORparameter) * mesh->nodesVector.nodes[j].phi;
						}
					}
					else
					{
						// Dirichlet boundary condition of phi = 0 at corner nodes
						mesh->nodesVector.nodes[j].phi = 0;
					}
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
					parametersList->logBrief("Solver convergence criteria met", 1);
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
		else if (parametersList->solverType == "FFT")
		{
			// TODO: Implement FFT based solver
		}
	}

	// TODO: Account for magnetic field
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

			if (parametersList->yBC == "periodic")
			{
				mesh->nodesVector.nodes[i].fields[1] = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].bottomNodeID - 1].phi -
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].periodicYNodeID - 1].phi) / (2 * h);
			}
			else
			{
				mesh->nodesVector.nodes[i].fields[1] = (mesh->nodesVector.nodes[i].phi -
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].bottomNodeID - 1].phi) / h;
			}
		}
		else if (mesh->nodesVector.nodes[i].boundaryType == "B")
		{
			mesh->nodesVector.nodes[i].fields[0] = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].leftNodeID - 1].phi -
				mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].rightNodeID - 1].phi) / (2 * h);

			if (parametersList->yBC == "periodic")
			{
				mesh->nodesVector.nodes[i].fields[1] = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].periodicYNodeID - 1].phi -
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].topNodeID - 1].phi) / (2 * h);
			}
			else
			{
				mesh->nodesVector.nodes[i].fields[1] = (mesh->nodesVector.nodes[i].phi - 
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].topNodeID - 1].phi) / h;
			}
		}
		else if (mesh->nodesVector.nodes[i].boundaryType == "L")
		{
			if (parametersList->xBC == "periodic")
			{
				mesh->nodesVector.nodes[i].fields[0] = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].periodicXNodeID - 1].phi -
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].rightNodeID - 1].phi) / (2 * h);
			}
			else
			{
				mesh->nodesVector.nodes[i].fields[0] = (mesh->nodesVector.nodes[i].phi - 
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].rightNodeID - 1].phi) / h;
			}

			mesh->nodesVector.nodes[i].fields[1] = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].bottomNodeID - 1].phi -
				mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].topNodeID - 1].phi) / (2 * h);
		}
		else if (mesh->nodesVector.nodes[i].boundaryType == "R")
		{
			if (parametersList->xBC == "periodic")
			{
				mesh->nodesVector.nodes[i].fields[0] = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].leftNodeID - 1].phi -
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].periodicXNodeID - 1].phi) / (2 * h);
			}
			else
			{
				mesh->nodesVector.nodes[i].fields[0] = (mesh->nodesVector.nodes[i].phi -
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].leftNodeID - 1].phi) / h;
			}

			mesh->nodesVector.nodes[i].fields[1] = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].bottomNodeID - 1].phi -
				mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].topNodeID - 1].phi) / (2 * h);
		}
		else if (mesh->nodesVector.nodes[i].boundaryType == "TL")
		{
			if (parametersList->xBC == "periodic")
			{
				mesh->nodesVector.nodes[i].fields[0] = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].periodicXNodeID - 1].phi -
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].rightNodeID - 1].phi) / (2 * h);
			}
			else
			{
				mesh->nodesVector.nodes[i].fields[0] = (mesh->nodesVector.nodes[i].phi -
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].rightNodeID - 1].phi) / h;
			}
			
			if (parametersList->yBC == "periodic")
			{
				mesh->nodesVector.nodes[i].fields[1] = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].bottomNodeID - 1].phi -
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].periodicYNodeID - 1].phi) / (2 * h);
			}
			else
			{
				mesh->nodesVector.nodes[i].fields[1] = (mesh->nodesVector.nodes[i].phi -
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].bottomNodeID - 1].phi) / h;
			}
		}
		else if (mesh->nodesVector.nodes[i].boundaryType == "BL")
		{
			if (parametersList->xBC == "periodic")
			{
				mesh->nodesVector.nodes[i].fields[0] = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].periodicXNodeID - 1].phi -
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].rightNodeID - 1].phi) / (2 * h);
			}
			else
			{
				mesh->nodesVector.nodes[i].fields[0] = (mesh->nodesVector.nodes[i].phi -
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].rightNodeID - 1].phi) / h;
			}
			
			if (parametersList->yBC == "periodic")
			{
				mesh->nodesVector.nodes[i].fields[1] = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].periodicYNodeID - 1].phi -
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].topNodeID - 1].phi) / (2 * h);
			}
			else
			{
				mesh->nodesVector.nodes[i].fields[1] = (mesh->nodesVector.nodes[i].phi - 
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].topNodeID - 1].phi) / h;
			}
		}
		else if (mesh->nodesVector.nodes[i].boundaryType == "TR")
		{
			if (parametersList->xBC == "periodic")
			{
				mesh->nodesVector.nodes[i].fields[0] = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].leftNodeID - 1].phi -
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].periodicXNodeID - 1].phi) / (2 * h);
			}
			else
			{
				mesh->nodesVector.nodes[i].fields[0] = (mesh->nodesVector.nodes[i].phi -
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].leftNodeID - 1].phi) / h;
			}

			if (parametersList->yBC == "periodic")
			{
				mesh->nodesVector.nodes[i].fields[1] = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].bottomNodeID - 1].phi -
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].periodicYNodeID - 1].phi) / (2 * h);
			}
			else
			{
				mesh->nodesVector.nodes[i].fields[1] = (mesh->nodesVector.nodes[i].phi -
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].bottomNodeID - 1].phi) / h;
			}
		}
		else if (mesh->nodesVector.nodes[i].boundaryType == "BR")
		{
			if (parametersList->xBC == "periodic")
			{
				mesh->nodesVector.nodes[i].fields[0] = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].leftNodeID - 1].phi -
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].periodicXNodeID - 1].phi) / (2 * h);
			}
			else
			{
				mesh->nodesVector.nodes[i].fields[0] = (mesh->nodesVector.nodes[i].phi -
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].leftNodeID - 1].phi) / h;
			}

			if (parametersList->yBC == "periodic")
			{
				mesh->nodesVector.nodes[i].fields[1] = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].periodicYNodeID - 1].phi -
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].topNodeID - 1].phi) / (2 * h);
			}
			else
			{
				mesh->nodesVector.nodes[i].fields[1] = (mesh->nodesVector.nodes[i].phi - 
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].topNodeID - 1].phi) / h;
			}
		}
	}
	parametersList->logBrief("Field solver exited", 1);
}

// Destructor
FieldSolver::~FieldSolver()
{
}