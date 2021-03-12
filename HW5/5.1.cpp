#include <iterator>
#include <locale>
#include <sstream>
#include <iostream>
#include <iomanip>

#include <Windows.h>

int main(int argc, char** argv)
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	double value_us;
	double value_rub;
	std::cin >> value_us;
	std::ostringstream usout;
	usout.imbue(std::locale("en_US.UTF-8"));
	usout << std::showbase << std::put_money(value_us * 100, false) << std::endl;
	std::cout << usout.str() << std::endl;

	value_rub = value_us * 80;
	std::ostringstream sout;
	sout.imbue(std::locale("ru_RU.UTF-8"));
	sout << std::showbase << std::put_money(value_rub * 100, false) << std::endl;
	std::cout << sout.str() << std::endl;

	system("pause");
	return 0;
}
