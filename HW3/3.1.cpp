#include "3.1 Header.hpp"

int main()
{
	std::cout << std::left << std::setw(10) << std::setfill(' ') << 'N' << std::setw(10) << std::setfill(' ') << "set_time"
		<< std::setw(10) << std::setfill(' ') << "vec_time" << '\n';
	for (auto n = 10; n < 1000001; n *= 10)
	{
		std::cout << std::left << std::setw(10) << std::setfill(' ') << n << std::setw(10) << std::setfill(' ') << counter(n).first
			<< std::setw(10) << std::setfill(' ') << counter(n).second << '\n';
	}

	return 0;
}


