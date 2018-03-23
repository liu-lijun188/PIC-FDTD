//! \file
//! \brief Implementation of Parameters class 
//! \author Rahul Kalampattel
//! \date Last updated March 2018

#include "Parameters.h"

// Default constructor
Parameters::Parameters()
{
}


// Constructor
Parameters::Parameters(std::string filename)
{
	initialTime = std::chrono::system_clock::now();
	std::ifstream inputFile(filename);	// Open input file
	
	char firstCharacter;
	std::string name;
	std::string value;

	if (inputFile.is_open())
	{
		logMessages("Reading inputs", __FILE__, __LINE__, 1);

		while (!inputFile.eof())	// Continue until the end of the file is reached
		{
			// Check what the first character in each line is
			firstCharacter = static_cast<char>(inputFile.get());

			// Check for commented or empty lines
			if (firstCharacter == '%' || firstCharacter == '\n')
			{
				inputFile.ignore(256, '\n');
			}
			// Store values in a string vector, names and values are space separated
			else
			{
				inputFile >> name >> value;
				valuesVector.push_back(value);
				inputFile.ignore(256, '\n');
			}
		}
		inputFile.close();
	}
	else
	{
		logMessages("Unable to open input file", __FILE__, __LINE__, 3);
		fileNotOpened = true;
	}
}


// Destructor
Parameters::~Parameters()
{
}


// Assign values to data members 
void Parameters::assignInputs()
{
	logMessages("Printing input parameters", __FILE__, __LINE__, 1);
	if (!fileNotOpened)
	{
		int index = 0;


		// Simulation parameters
		try
		{
			timeStep = stod(valuesVector[index]);
			if (timeStep < 0.0)
			{
				throw 1;
			}
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid type detected for time step", 3);
		}
		catch (int error)
		{
			logBrief("Time step should be positive", 3);
		}
		logBrief("Time step: " + valuesVector[index], 1);
		index++;


		try
		{
			maximumNumberOfIterations = stoi(valuesVector[index]);
			if (maximumNumberOfIterations < 0)
			{
				throw 1;
			}
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for maximum number of iterations", 3);
		}
		catch (int error)
		{
			logBrief("Maximum number of iterations should be positive", 3);
		}
		logBrief("Maximum number of iterations: " + valuesVector[index], 1);
		index++;


		try
		{
			numberOfPatches = stoi(valuesVector[index]);
			if (numberOfPatches < 0)
			{
				throw 1;
			}
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for number of patches", 3);
		}
		catch (int error)
		{
			logBrief("Number of patches should be positive", 3);
		}
		logBrief("Number of patches: " + valuesVector[index], 1);
		index++;


		try
		{
			particlesPerCell = stoi(valuesVector[index]);
			if (particlesPerCell < 1)
			{
				throw 1;
			}
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for particles per cell", 3);
		}
		catch (int error)
		{
			logBrief("Particles per cell should be positive", 3);
		}
		logBrief("Particles per cell: " + valuesVector[index], 1);
		index++;


		try
		{
			numCellsWithParticles = stoi(valuesVector[index]);
			if (numCellsWithParticles < 0)
			{
				throw 1;
			}
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for number of cells with particles", 3);
		}
		catch (int error)
		{
			logBrief("Number of cells with particles should be positive", 3);
		}
		logBrief("Number of cells with particles: " + valuesVector[index], 1);
		index++;


		try
		{
			simulationType = valuesVector[index];
			if (simulationType == "full" || simulationType == "partial" || simulationType == "electron")
			{
			}
			else
			{
				throw 1;
			}
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for simulation type", 3);
		}
		catch (int error)
		{
			logBrief("Simulation type should be full, partial, or electron", 3);
		}
		logBrief("Simulation type: " + valuesVector[index], 1);
		index++;


		try
		{
			int value = stoi(valuesVector[index]);
			if (value == 1)
			{
				axisymmetric = true;
			}
			else if (value == 0)
			{
				axisymmetric = false;
			}
			else
			{
				throw 1;
			}
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for axisymmetric flag", 3);
		}
		catch (int error)
		{
			logBrief("Axisymmetric flag should be true (1) or false (0)", 3);
		}
		logBrief("Axisymmetric flag: " + valuesVector[index], 1);
		index++;


		try
		{
			int value = stoi(valuesVector[index]);
			if (value == 1)
			{
				twoStream = true;
			}
			else if (value == 0)
			{
				twoStream = false;
			}
			else
			{
				throw 1;
			}
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for two-stream flag", 3);
		}
		catch (int error)
		{
			logBrief("Two-stream flag should be true (1) or false (0)", 3);
		}
		logBrief("Two-stream flag: " + valuesVector[index], 1);
		index++;


		// Particle parameters
		try
		{
			particleDistribution = valuesVector[index];
			if (particleDistribution == "uniform" || particleDistribution == "random" || particleDistribution == "precise")
			{
			}
			else
			{
				throw 1;
			}
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for particle distribution", 3);
		}
		catch (int error)
		{
			logBrief("Particle distribution should be uniform, random or precise", 3);
		}
		logBrief("Particle distribution: " + valuesVector[index], 1);
		index++;


		try
		{
			std::stringstream inputs(valuesVector[index]);
			std::vector<std::string> outputs;

			while (inputs.good())
			{
				std::string value;
				std::getline(inputs, value, ',');
				outputs.push_back(value);
			}

			for (int i = 0; i < outputs.size(); i++)
			{
				initialPosition.push_back(stod(outputs[i]));
				if (initialPosition[i] < 0.0 || initialPosition[i] > 1.0)
				{
					throw 1;
				}
			}
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for initial position", 3);
		}
		catch (int error)
		{
			logBrief("Initial position should be between 0 and 1", 3);
		}
		logBrief("Initial position: " + valuesVector[index], 1);
		index++;


		try
		{
			std::stringstream inputs(valuesVector[index]);
			std::vector<std::string> outputs;

			while (inputs.good())
			{
				std::string value;
				std::getline(inputs, value, ',');
				outputs.push_back(value);
			}

			for (int i = 0; i < outputs.size(); i++)
			{
				initialVelocity.push_back(stod(outputs[i]));
			}
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for initial velocity", 3);
		}
		logBrief("Initial velocity: " + valuesVector[index], 1);
		index++;


		try
		{
			propellant = valuesVector[index];
			if (propellant != "xenon")
			{
				throw 1;
			}
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for propellant", 3);
		}
		catch (int error)
		{
			logBrief("Invalid propellant selected", 3);
		}
		logBrief("Propellant: " + valuesVector[index], 1);
		index++;


		// Field parameters
		try
		{
			std::stringstream inputs(valuesVector[index]);
			std::vector<std::string> outputs;

			while (inputs.good())
			{
				std::string value;
				std::getline(inputs, value, ',');
				outputs.push_back(value);
			}

			for (int i = 0; i < outputs.size(); i++)
			{
				Efield.push_back(stod(outputs[i]));
			}
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for electric field", 3);
		}
		logBrief("Electric field: " + valuesVector[index], 1);
		index++;


		try
		{
			std::stringstream inputs(valuesVector[index]);
			std::vector<std::string> outputs;

			while (inputs.good())
			{
				std::string value;
				std::getline(inputs, value, ',');
				outputs.push_back(value);
			}

			for (int i = 0; i < outputs.size(); i++)
			{
				Bfield.push_back(stod(outputs[i]));
			}
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for magnetic field", 3);
		}
		logBrief("Magnetic field: " + valuesVector[index], 1);
		index++;


		try
		{
			FDTDtimeStep = stod(valuesVector[index]);
			if (FDTDtimeStep < 0.0)
			{
				throw 1;
			}
		}
		catch (const std::exception&)
		{
			logBrief("Invalid argument detected for FDTD time step", 3);
		}
		catch (int error)
		{
			logBrief("FDTD time step should be positive", 3);
		}
		logBrief("FDTD time step: " + valuesVector[index], 1);
		index++;


		// Mesh parameters
		try
		{
			meshFilePath = valuesVector[index];
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for mesh file path", 3);
		}
		logBrief("Mesh file path: " + valuesVector[index], 1);
		index++;


		try
		{
			meshScalingParameter = stod(valuesVector[index]);
		}
		catch (const std::exception&)
		{
			logBrief("Invalid argument detected for mesh scaling parameter", 3);
		}
		logBrief("Mesh scaling parameter: " + valuesVector[index], 1);
		index++;


		// Solver parameters
		try
		{
			solverType = valuesVector[index];
			if (solverType == "GS" || solverType == "FFT")
			{
			}
			else
			{
				throw 1;
			}
		}
		catch (const std::exception&)
		{
			logBrief("Invalid argument detected for solver type", 3);
		}
		catch (int error)
		{
			logBrief("Solver type should be GS or FFT", 3);
		}
		logBrief("Solver type: " + valuesVector[index], 1);
		index++;


		try
		{
			maxSolverIterations = stoi(valuesVector[index]);
			if (maxSolverIterations < 0)
			{
				throw 1;
			}
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for maximum solver iterations", 3);
		}
		catch (int error)
		{
			logBrief("Maximum solver iterations should be positive", 3);
		}
		logBrief("Maximum solver iterations: " + valuesVector[index], 1);
		index++;


		try
		{
			residualTolerance = stod(valuesVector[index]);
			if (residualTolerance < 0.0)
			{
				throw 1;
			}
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for residual tolerance", 3);
		}
		catch (int error)
		{
			logBrief("Residual tolerance should be positive", 3);
		}
		logBrief("Residual tolerance: " + valuesVector[index], 1);
		index++;


		try
		{
			SORparameter = stod(valuesVector[index]);
			if (SORparameter < 1.0)
			{
				throw 1;
			}
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for successive over-relaxation parameter", 3);
		}
		catch (int error)
		{
			logBrief("Successive over-relaxation parameter should be positive", 3);
		}
		logBrief("Successive over-relaxation parameter: " + valuesVector[index], 1);
		index++;


		try
		{
			leftBCType = valuesVector[index];
			if (leftBCType == "periodic" || leftBCType == "open" || leftBCType == "dirichlet" || leftBCType == "neumann")
			{
			}
			else
			{
				throw 1;
			}
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for left boundary condition type", 3);
		}
		catch (int error)
		{
			logBrief("Left boundary condition type should be periodic, open, dirichlet or neumann", 3);
		}
		logBrief("Left boundary condition type: " + valuesVector[index], 1);
		index++;


		try
		{
			leftBCValue = stod(valuesVector[index]);
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for left boundary condition value", 3);
		}
		logBrief("Left boundary condition value: " + valuesVector[index], 1);
		index++;


		try
		{
			rightBCType = valuesVector[index];
			if (rightBCType == "periodic" || rightBCType == "open" || rightBCType == "dirichlet" || rightBCType == "neumann")
			{
			}
			else
			{
				throw 1;
			}
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for right boundary condition type", 3);
		}
		catch (int error)
		{
			logBrief("Right boundary condition type should be periodic, open, dirichlet or neumann", 3);
		}
		if ((rightBCType == "periodic" && leftBCType != "periodic") || (rightBCType != "periodic" && leftBCType == "periodic"))
		{
			logBrief("Periodic boundary conditions must be used on left and right", 3);
		}
		logBrief("Right boundary condition type: " + valuesVector[index], 1);
		index++;


		try
		{
			rightBCValue = stod(valuesVector[index]);
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for right boundary condition value", 3);
		}
		logBrief("Right boundary condition value: " + valuesVector[index], 1);
		index++;


		try
		{
			topBCType = valuesVector[index];
			if (topBCType == "periodic" || topBCType == "open" || topBCType == "dirichlet" || topBCType == "neumann")
			{
			}
			else
			{
				throw 1;
			}
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for top boundary condition type", 3);
		}
		catch (int error)
		{
			logBrief("Top boundary condition type should be periodic, open, dirichlet or neumann", 3);
		}
		logBrief("Top boundary condition type: " + valuesVector[index], 1);
		index++;


		try
		{
			topBCValue = stod(valuesVector[index]);
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for top boundary condition value", 3);
		}
		logBrief("Top boundary condition value: " + valuesVector[index], 1);
		index++;


		try
		{
			bottomBCType = valuesVector[index];
			if (bottomBCType == "periodic" || bottomBCType == "open" || bottomBCType == "dirichlet" || bottomBCType == "neumann")
			{
			}
			else
			{
				throw 1;
			}
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for bottom boundary condition type", 3);
		}
		catch (int error)
		{
			logBrief("Bottom boundary condition type should be periodic, open, dirichlet or neumann", 3);
		}
		if ((bottomBCType == "periodic" && topBCType != "periodic") || (bottomBCType != "periodic" && topBCType == "periodic"))
		{
			logBrief("Periodic boundary conditions must be used on top and bottom", 3);
		}
		logBrief("Bottom boundary condition type: " + valuesVector[index], 1);
		index++;


		try
		{
			bottomBCValue = stod(valuesVector[index]);
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for bottom boundary condition value", 3);
		}
		logBrief("Bottom boundary condition value: " + valuesVector[index], 1);
		index++;


		// Parallelisation parameters
		try
		{
			numThreads = stoi(valuesVector[index]);
			if (numThreads < 1)
			{
				throw 1;
			}
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for number of OpenMP threads", 3);
		}
		catch (int error)
		{
			logBrief("Number of threads should be greater than 0", 3);
		}
		logBrief("Number of OpenMP threads: " + valuesVector[index], 1);
		index++;


		// Output parameters
		try
		{
			plotFrequency = stoi(valuesVector[index]);
			if (plotFrequency < 0)
			{
				throw 1;
			}
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for plotting frequency", 3);
		}
		catch (int error)
		{
			logBrief("Plotting frequency should be positive", 3);
		}
		logBrief("Plotting frequency: " + valuesVector[index], 1);
		index++;


		try
		{
			tecplotMesh = valuesVector[index];
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for output mesh file name", 3);
		}
		logBrief("Output mesh file name: " + valuesVector[index], 1);
		index++;


		try
		{
			tecplotParticleSolution = valuesVector[index];
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for particle solution file name", 3);
		}
		logBrief("Particle solution file name: " + valuesVector[index], 1);
		index++;


		try
		{
			tecplotNodeSolution = valuesVector[index];
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for node solution file name", 3);
		}
		logBrief("Node solution file name: " + valuesVector[index], 1);
		index++;


		try
		{
			tecplotGlobalSolution = valuesVector[index];
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for global solution file name", 3);
		}
		logBrief("Global solution file name: " + valuesVector[index], 1);
		index++;
	}
}


// Process mesh file
void Parameters::processMesh()
{
	logMessages("Extracting mesh data", __FILE__, __LINE__, 1);

	precessingGridSU2(meshFilePath, meshFile);
	readGridFromFile(meshFile + ".op2", gridinfo, gridgeo);
	processingGrid(gridinfo, gridgeo);
}


// Log messages, warnings and errors
void Parameters::logMessages(std::string message, std::string filename, int line, int messageType)
{
	std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();
	std::chrono::duration<double> duration;
	duration = currentTime - initialTime;

	if (!firstLog)
	{
		std::ofstream logFile("logFile.txt", std::ios::app);	// Open log file, 'append' write mode

		if (logFile.is_open())
		{	
			if (messageType == 1)
			{
				logFile << std::left << std::setfill('.') << std::setw(45) << "(" +
					filename + ", line " + std::to_string(line) + ")" << message <<
					std::right << std::setw(100 - message.length()) << "Elapsed time: " +
					std::to_string(duration.count()) + " seconds" << std::endl;
			}
			else if (messageType == 2)
			{
				logFile << std::left << std::setfill('.') << std::setw(45) << "(" +
					filename + ", line " + std::to_string(line) + ")" << "## WARNING: " +
					message << std::right << std::setw(100 - message.length()) << 
					"Elapsed time: " + std::to_string(duration.count()) + " seconds" <<
					std::endl;
			}
			else if (messageType == 3)
			{
				logFile << std::left << std::setfill('.') << std::setw(45) << "(" +
					filename + ", line " + std::to_string(line) + ")" << "#### ERROR: " + 
					message << std::right << std::setw(100 - message.length()) << 
					"Elapsed time: " + std::to_string(duration.count()) + " seconds" <<
					std::endl;
				numErrors += 1;
			}
			logFile.close();
		}
		else
		{
			std::cout << "Unable to open log file!!!" << std::endl;
		}
		std::cout << message << std::endl;
	}
	else
	{
		std::ofstream logFile("logFile.txt", std::ios::trunc);	// Open log file, 'truncate' write mode

		if (logFile.is_open())
		{
			std::time_t clockTime = std::chrono::system_clock::to_time_t(currentTime);
			logFile << "Simulation start time: " << std::ctime(&clockTime) << std::endl;
			
			logFile << std::left << std::setfill('.') << std::setw(45) << "(" + 
				filename + ", line " + std::to_string(line) + ")" << message << 
				std::right << std::setw(100 - message.length()) << "Elapsed time: " + 
				std::to_string(duration.count()) + " seconds" << std::endl;
			logFile.close();
		}
		else
		{
			std::cout << "Unable to open log file!!!" << std::endl;
		}
		std::cout << message << std::endl;
		firstLog = false;
	}

}


// Log brief messages
void Parameters::logBrief(std::string message, int messageType)
{
	std::ofstream logFile("logFile.txt", std::ios::app);	// Open log file, 'append' write mode

	if (logFile.is_open())
	{
		if (messageType == 1)
		{
			logFile << std::left << std::setw(45) << " " << message << std::endl;
			logFile.close();
		}
		else if (messageType == 2)
		{
			logFile << std::left << std::setw(45) << " " << "## WARNING: " + message << std::endl;
			logFile.close();
		}
		else if (messageType == 3)
		{
			logFile << std::left << std::setw(45) << " " << "#### ERROR: " + message << std::endl;
			logFile.close();
			numErrors += 1;
		}
	}
	else
	{
		std::cout << "Unable to open log file!!!" << std::endl;
	}
	std::cout << message << std::endl;
}