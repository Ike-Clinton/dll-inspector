// dll-inspector.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "public.h"

// namespace for error messages

int main(int argc, char** argv) {
	try {
		std::string dllName = "";
		if (argc == 1) {
			printf("Usage: dll-inspector.exe --inputFile [input.dll] [options]\n");
			return 0;
		}
		// Use Boost program_options for arg parsing
		namespace po = boost::program_options;

		// Declare command line args and their descriptions
		po::options_description desc("Options");
		desc.add_options()
			("help,h", "Print program usage")
			("inputFile,i", po::value<std::string>(), "The DLL we are going to load")
			("showFunctions,s", "Display all functions in the given DLL")
			("loadLibrary,l", "Wrapper for LoadLibrary");

		// Map all the args to a variables_map called vm
		po::variables_map vm;
		try
		{
			// store the allowed command args in "vm"
			po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);

			// Store the filename of the input dll here
			
			
			// "--help" option for usage information
			if (vm.count("help"))
			{
				printf("Usage: dll-inspector.exe --inputFile [input.dll] [options]\n");
				std::cout << desc << std::endl;
				return 0;
			}
			else if (vm.count("inputFile")) {
				// Name of the dll e.g. "test.dll"
				dllName = vm["inputFile"].as<std::string>();
			}

			// User specified a .dll file, let's process their commands
			// "--showFunctions"
			if (vm.count("showFunctions")) {
				printf("Showing functions from %s:\n\n", dllName.c_str());
				showFunctions(dllName);
			}

			// "--loadFunction myFunc"
			else if (vm.count("loadLibrary")) {

				printf("Loading %s:\n\n", dllName.c_str());
				loadLibrary(dllName);
			}
		// throws on error, so do after help in case there are errors
		po::notify(vm);
		}
		catch (po::error& e)
		{
			std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
			std::cerr << desc << std::endl;
			return 1;
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Unhandled Exception reached the top of main: "
			<< e.what() << ", application will now exit" << std::endl;
		return 2;
	}
	return 0;
}