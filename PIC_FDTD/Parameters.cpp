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
		// Constants
		try
		{
			epsilon0 = stod(valuesVector[0]);
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for permittivity", 3);
		}
		logBrief("Permittivity: " + valuesVector[0], 1);


		// Simulation parameters
		try
		{
			timeStep = stod(valuesVector[1]);
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
		logBrief("Time step: " + valuesVector[1], 1);


		try
		{
			maximumNumberOfIterations = stoi(valuesVector[2]);
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
		logBrief("Maximum number of iterations: " + valuesVector[2], 1);


		try
		{
			numberOfPatches = stoi(valuesVector[3]);
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
		logBrief("Number of patches: " + valuesVector[3], 1);


		try
		{
			particlesPerCell = stoi(valuesVector[4]);
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
		logBrief("Particles per cell: " + valuesVector[4], 1);


		try
		{
			numCellsWithParticles = stoi(valuesVector[5]);
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
		logBrief("Number of cells with particles: " + valuesVector[5], 1);


		try
		{
			int value = stoi(valuesVector[6]);
			if (value == 1)
			{
				axisymmetric = true;
			}
			else if (value == 0)
			{
				axisymmetric == false;
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
		logBrief("Axisymmetric flag: " + valuesVector[6], 1);


		try
		{
			int value = stoi(valuesVector[7]);
			if (value == 1)
			{
				twoStream = true;
			}
			else if (value == 0)
			{
				twoStream == false;
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
		logBrief("Two-stream flag: " + valuesVector[7], 1);


		// Particle parameters
		try
		{
			charge = stod(valuesVector[8]);
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for charge", 3);
		}
		logBrief("Particle charge: " + valuesVector[8], 1);


		try
		{
			mass = stod(valuesVector[9]);
			if (mass < 0.0)
			{
				throw 1;
			}
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for mass", 3);
		}
		catch (int error)
		{
			logBrief("Mass should be positive", 3);
		}
		logBrief("Particle mass: " + valuesVector[9], 1);
	

		try
		{
			xInitial = stod(valuesVector[10]);
			if (xInitial < 0.0 || xInitial > 1.0)
			{
				throw 1;
			}
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for initial x position", 3);
		}
		catch (int error)
		{
			logBrief("Initial x position should be between 0 and 1", 3);
		}
		logBrief("Initial x position: " + valuesVector[10], 1);


		try
		{
			yInitial = stod(valuesVector[11]);
			if (yInitial < 0.0 || xInitial > 1.0)
			{
				throw 1;
			}
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for initial y position", 3);
		}
		catch (int error)
		{
			logBrief("Initial y position should be between 0 and 1", 3);
		}
		logBrief("Initial y position: " + valuesVector[11], 1);


		try
		{
			uInitial = stod(valuesVector[12]);
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for initial x velocity", 3);
		}
		logBrief("Initial x velocity: " + valuesVector[12], 1);


		try
		{
			vInitial = stod(valuesVector[13]);
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for initial y velocity", 3);
		}
		logBrief("Initial y velocity: " + valuesVector[13], 1);


		try
		{
			xPerturbation = stod(valuesVector[14]);
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for initial x perturbation", 3);
		}
		logBrief("Initial x perturbation: " + valuesVector[14], 1);


		try
		{
			yPerturbation = stod(valuesVector[15]);
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for initial y perturbation", 3);
		}
		logBrief("Initial y perturbation: " + valuesVector[15], 1);


		// Field parameters
		try
		{
			xEfield = stod(valuesVector[16]);
		}
		catch (const std::exception&)
		{
			logBrief("Invalid argument detected for x electric field", 3);
		}
		logBrief("Electric field in x direction: " + valuesVector[16], 1);

		try
		{
			yEfield = stod(valuesVector[17]);
		}
		catch (const std::exception&)
		{
			logBrief("Invalid argument detected for y electric field", 3);
		}
		logBrief("Electric field in y direction: " + valuesVector[17], 1);

		try
		{
			zBfield = stod(valuesVector[18]);
		}
		catch (const std::exception&)
		{
			logBrief("Invalid argument detected for z magnetic field", 3);
		}
		logBrief("Magnetic field in z direction: " + valuesVector[18], 1);

		try
		{
			FDTDtimeStep = stod(valuesVector[19]);
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
		logBrief("FDTD time step in y direction: " + valuesVector[19], 1);


		// Mesh parameters
		try
		{
			meshFilePath = valuesVector[20];
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for mesh file path", 3);
		}
		logBrief("Mesh file path: " + valuesVector[20], 1);


		try
		{
			meshScalingParameter = stod(valuesVector[21]);
			if (meshScalingParameter < 0.0)
			{
				throw 1;
			}
		}
		catch (const std::exception&)
		{
			logBrief("Invalid argument detected for mesh scaling parameter", 3);
		}
		catch (int error)
		{
			logBrief("Mesh scaling parameter should be positive", 3);
		}
		logBrief("Mesh scaling parameter: " + valuesVector[21], 1);


		// Solver parameters
		try
		{
			solverType = valuesVector[22];
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
		logBrief("Solver type: " + valuesVector[22], 1);


		try
		{
			maxSolverIterations = stoi(valuesVector[23]);
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
		logBrief("Maximum solver iterations: " + valuesVector[23], 1);


		try
		{
			residualTolerance = stod(valuesVector[24]);
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
		logBrief("Residual tolerance: " + valuesVector[24], 1);


		try
		{
			SORparameter = stod(valuesVector[25]);
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
		logBrief("Successive over-relaxation parameter: " + valuesVector[25], 1);


		try
		{
			xBCType = valuesVector[26];
			if (xBCType == "periodic" || xBCType == "dirichlet" || xBCType == "neumann")
			{
			}
			else
			{
				throw 1;
			}
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for x boundary condition type", 3);
		}
		catch (int error)
		{
			logBrief("Boundary condition x type should be periodic, dirichlet or neumann", 3);
		}
		logBrief("Boundary condition x type: " + valuesVector[26], 1);


		try
		{
			xBCValue = stod(valuesVector[27]);
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for x boundary condition value", 3);
		}
		logBrief("Boundary condition x value: " + valuesVector[27], 1);


		try
		{
			yBCType = valuesVector[28];
			if (yBCType == "periodic" || yBCType == "dirichlet" || yBCType == "neumann")
			{
			}
			else
			{
				throw 1;
			}
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for y boundary condition type", 3);
		}
		catch (int error)
		{
			logBrief("Boundary condition y type should be periodic, dirichlet or neumann", 3);
		}
		logBrief("Boundary condition y type: " + valuesVector[28], 1);


		try
		{
			yBCValue = stod(valuesVector[29]);
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for y boundary condition value", 3);
		}
		logBrief("Boundary condition y value: " + valuesVector[29], 1);


		// Parallelisation parameters
		try
		{
			numThreads = stoi(valuesVector[30]);
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
		logBrief("Number of OpenMP threads: " + valuesVector[30], 1);


		// Output parameters
		try
		{
			plotFrequency = stoi(valuesVector[31]);
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
		logBrief("Plotting frequency: " + valuesVector[31], 1);
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