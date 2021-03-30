#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>


template < typename Iterator, typename Function>
void parallel_for_each(Iterator first, Iterator last, Function function, std::size_t max_block_size)
{
	auto length = std::distance(first, last);

	if (length < max_block_size)
	{
		std::for_each(first, last, function);
	}
	else
	{

		Iterator middle = first;
		std::advance(middle, length / 2);

		std::future < void > first_half_result = std::async
		(parallel_for_each < Iterator, Function >, first, middle, function, max_block_size);

		parallel_for_each(middle, last, function, max_block_size);

		first_half_result.get();
	}
}

int main(int argc, char** argv)
{
	std::vector < int > v(1000000);

	std::iota(v.begin(), v.end(), 0);

	/*std::for_each(v.begin(), v.end(), [](auto& kal) {kal *= 2; });
	std::cout << "privet";*/

	parallel_for_each(v.begin(), v.end(), [](auto& kal) {kal *= 2; }, v.size()/std::thread::hardware_concurrency());

	std::cout << v[35] << std::endl;

	system("pause");

	return EXIT_SUCCESS;
}
