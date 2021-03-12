#include <algorithm>
#include <iostream>
#include <regex>
#include <string>
#include <iomanip>

int main(int argc, char** argv)
{
	std::string data = "mail:: gorshkov.ap@phystech.edu popov@phystech.edu makarov@phystech.edu ivanov@gmail.com ultima@mail.ru privet@mail.com google123@gmail.com roughly@mail 123@mail.ru my@mail.mipt.ru ru mail@mail.ru  not@mail.runot";

	std::regex pattern(R"((\w+\.{0,1})+@(([[:alpha:]]+\.)+\w{2,}))");

	std::sregex_iterator begin(data.cbegin(), data.cend(), pattern);
	std::sregex_iterator end;

	std::for_each(begin, end, [](const std::smatch& m) {std::cout << std::left << std::setw(25) << m[0] << " | " << m[2];
	std::cout << std::endl; });

	return EXIT_SUCCESS;
}