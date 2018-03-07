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
		try
		{
			timeStep = stod(valuesVector[0]);
			if (timeStep < 0.0)
				throw 1;
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid type detected for time step", 3);
		}
		catch (int error)
		{
			logBrief("Time step should be positive", 3);
		}
		logBrief("Time step: " + valuesVector[0], 1);


		try
		{
			maximumNumberOfIterations = stoi(valuesVector[1]);
			if (maximumNumberOfIterations < 0)
				throw 1;
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for maximum number of iterations", 3);
		}
		catch (int error)
		{
			logBrief("Maximum number of iterations should be positive", 3);
		}
		logBrief("Maximum number of iterations: " + valuesVector[1], 1);


		try
		{
			numberOfPatches = stoi(valuesVector[2]);
			if (numberOfPatches < 0)
				throw 1;
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for number of patches", 3);
		}
		catch (int error)
		{
			logBrief("Number of patches should be positive", 3);
		}
		logBrief("Number of patches: " + valuesVector[2], 1);


		try
		{
			particlesPerCell = stoi(valuesVector[3]);
			if (particlesPerCell < 1)
				throw 1;
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for particles per cell", 3);
		}
		catch (int error)
		{
			logBrief("Particles per cell should be positive", 3);
		}
		logBrief("Particles per cell: " + valuesVector[3], 1);


		try
		{
			charge = stod(valuesVector[4]);
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for charge", 3);
		}
		logBrief("Charge: " + valuesVector[4], 1);


		try
		{
			mass = stod(valuesVector[5]);
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
		logBrief("Mass: " + valuesVector[5], 1);


		try
		{
			maxSolverIterations = stoi(valuesVector[6]);
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
		logBrief("Maximum solver iterations: " + valuesVector[6], 1);


		try
		{
			residualTolerance = stod(valuesVector[7]);
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
		logBrief("Residual tolerance: " + valuesVector[7], 1);


		try
		{
			SORparameter = stod(valuesVector[8]);
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
		logBrief("Successive over-relaxation parameter: " + valuesVector[8], 1);


		try
		{
			epsilon0 = stod(valuesVector[9]);
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for permittivity", 3);
		}
		logBrief("Permittivity: " + valuesVector[9], 1);


		try
		{
			meshFilePath = valuesVector[10];
		}
		catch (std::invalid_argument&)
		{
			logBrief("Invalid argument detected for mesh file path", 3);
		}
		logBrief("Mesh file path: " + valuesVector[10], 1);


		xTest = stod(valuesVector[11]);
		logBrief("xTest: " + valuesVector[11], 1);


		yTest = stod(valuesVector[12]);
		logBrief("yTest: " + valuesVector[12], 1);
	

		uTest = stod(valuesVector[13]);
		logBrief("uTest: " + valuesVector[13], 1);


		vTest = stod(valuesVector[14]);
		logBrief("vTest: " + valuesVector[14], 1);


		xPerturbation = stod(valuesVector[15]);
		logBrief("xPerturbation: " + valuesVector[15], 1);
		

		yPerturbation = stod(valuesVector[16]);
		logBrief("yPerturbation: " + valuesVector[16], 1);
		

		numCellsWithParticles = stoi(valuesVector[17]);
		logBrief("numCellsWithParticles: " + valuesVector[17], 1);

		plotFrequency = stoi(valuesVector[18]);
		logBrief("plotFrequency: " + valuesVector[18], 1);

		meshScalingParameter = stod(valuesVector[19]);
		logBrief("meshScalingParameter: " + valuesVector[19], 1);

		solverType = valuesVector[20];
		logBrief("solverType: " + valuesVector[20], 1);

		xBC = valuesVector[21];
		logBrief("xBC: " + valuesVector[21], 1);

		yBC = valuesVector[22];
		logBrief("yBC: " + valuesVector[22], 1);

		twoStream = stoi(valuesVector[23]);
		logBrief("twoStream: " + valuesVector[23], 1);
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