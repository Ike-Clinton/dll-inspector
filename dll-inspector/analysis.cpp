#include "stdafx.h"
#include "public.h"


//  Given a function name, attempt to load the function from the DLL
void loadFunction(std::string dllName, std::string functionName) {
	printf("Loading %s from %s:\n", dllName.c_str(), functionName.c_str());
	// Load the library, windows automatically calls DLLmain

	// convert string to LPWCSTR
	std::wstring temp = s2ws(dllName);
	LPCWSTR result = temp.c_str();
	HMODULE dll = LoadLibrary(result);
}

// Show all the functions in the given DLL and print them to stdout
void showFunctions(std::string dllName) {
	printf("Test\n");
}