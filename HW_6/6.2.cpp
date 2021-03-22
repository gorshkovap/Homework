#include <filesystem>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string> 


int main()
{
	std::fstream fin("file.txt", std::ios::in);
	std::string string;
	std::getline(fin, string);
	std::size_t size = std::size(string);
	std::size_t num;
	std::cout << "Add the number of string ";
	std::cin >> num;
	fin.seekg((num - 1) * (size + 2));
	std::getline(fin, string);
	if (fin.eof())
		std::cerr << "Current" << std::endl;
	else
	{

	}
		std::cout << string << std::endl;
	system("pause");

	return EXIT_SUCCESS;
}