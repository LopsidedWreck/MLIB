// mlib.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "mlib.hpp"


int main()
{
	/* mlib::ParseFile Test */

	// Create a file object.
	std::ifstream in_file;
	char seperating_character = ':';
	const char* file_name = "./ParseFileTest.txt";

	std::vector<std::string> test_output = 
		mlib::ParseFile(in_file, seperating_character, file_name); // Parse file.

	// Print out the output.
	for (UINT i = 0; i < test_output.size(); ++i)
		std::cout << test_output.at(i) << std::endl;

	return 0;
}
