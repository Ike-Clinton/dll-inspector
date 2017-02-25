// dll-inspector.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "public.h"
#include "prototypes.h"

// namespace for error messages
namespace
{
	const size_t ERROR_IN_COMMAND_LINE = 1;
	const size_t SUCCESS = 0;
	const size_t ERROR_UNHANDLED_EXCEPTION = 2;


int main(int argc, char** argv)
{
	try
	{
		/** Define and parse the program options
		*/
		namespace po = boost::program_options;
		
		po::options_description desc("Options");
		desc.add_options()
			("help,h", "Print program usage")
			("show-functions,s", "Display all functions in the given DLL")
			("load-function,l", po::value<char*>(), "Loads and runs specified function if given, otherwise loads DLLMain");

		// Positional argument required for the dll we are going to run
		po::positional_options_description positionalOptions;
		positionalOptions.add("test", 1);

		// Map all the args to a variables_map called vm
		po::variables_map vm;
		try
		{
			po::store(po::command_line_parser(argc, argv).options(desc)
				.positional(positionalOptions).run(),
				vm);

			// "--help" option
			if (vm.count("help"))
			{
				std::cout << "Simple DLL inspector" << std::endl
					<< desc << std::endl;
				return SUCCESS;
			}
			po::notify(vm); // throws on error, so do after help in case 
							// there are any problems 

			if (vm.count("show-functions")) {
				std::cout << "Showing functions from DLL\n" << std::endl;
				if (functionName != "DLLMain") {
					showFunctions(dllName, function);
				}
				else {
					showFunctions(dllName);
				}
				
			}

			if (vm.count("load")) {
				std::cout << "Loading" + function + " from " + dll_filename;
			}

		}
		catch (po::error& e)
		{
			std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
			std::cerr << desc << std::endl;
			return ERROR_IN_COMMAND_LINE;
		}

		// application code here // 

	}
	catch (std::exception& e)
	{
		std::cerr << "Unhandled Exception reached the top of main: "
			<< e.what() << ", application will now exit" << std::endl;
		return ERROR_UNHANDLED_EXCEPTION;

	}

	return SUCCESS;

} // main 