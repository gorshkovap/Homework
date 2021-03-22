#include <iostream>
#include <fstream>
#include <string> 


int main()
{
	std::fstream fin("file.txt", std::ios::in);
	std::string s;
	std::getline(fin, s);
	std::size_t size = std::size(s);

	std::size_t num;
	std::cout << "Enter number of line: ";
	std::cin >> num;

	fin.seekg((num - 1) * (size + 2));
	std::getline(fin, s);
	if (fin.eof())
		std::cerr << "EOF!" << std::endl;
	else
		std::cout << s << std::endl;
	return EXIT_SUCCESS;
}