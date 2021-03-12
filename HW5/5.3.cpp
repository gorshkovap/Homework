
#include <algorithm>
#include <iostream>
#include <regex>
#include <string>

int main(int argc, char** argv)
{
	std::string data = "21/02/2002 01/02/2020 23/01/2032 11/11/1012 13/24/5666 23/12/8900 12:01:10 8:15:12 00:00:00 23:59:59 14:00:00 24:00:00 25:00:00";

	std::regex pattern_1(R"((0[1-9]|[12][0-9]|3[01])[- /.](0[1-9]|1[012])[- /.](19|20)\d\d)");
	std::regex pattern_2("([01]?[0-9]|2[0-3]):[0-5][0-9]");

	std::copy(
		std::sregex_token_iterator(data.begin(), data.end(), pattern_1, { 0 }),
		std::sregex_token_iterator(),
		std::ostream_iterator < std::string >(std::cout, "\n"));

	std::cout << std::endl;

	std::copy(
		std::sregex_token_iterator(data.begin(), data.end(), pattern_2, { 0 }),
		std::sregex_token_iterator(),
		std::ostream_iterator < std::string >(std::cout, "\n"));

	system("pause");

	return EXIT_SUCCESS;
}
