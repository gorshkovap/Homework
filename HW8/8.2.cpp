#include <iostream>
#include <algorithm>
#include <thread>
#include <string>
#include <mutex>
#include <vector>
#include <cstring>

std::mutex mtx;

void FindDNA(const std::string& base, const std::string& find, std::size_t left, std::size_t right, 
std::vector <std::size_t>& vector)
{
	std::size_t t = std::size(find);
	for (auto i = left; i < right; i++)
	{
		bool flag = true;
		for (auto n = 0U; n < t; n++)
		{
			if (base[i + n] != find[n])
				flag = false;
		}
		if (flag)
		{
			std::lock_guard lg(mtx);
			vector.push_back(i);
		}
	}
}

void MultyFindDNA(const std::string& base, const std::string& find, std::vector <std::size_t>& vector)
{
	std::size_t NThread = std::thread::hardware_concurrency();
	std::vector<std::thread> threads;
	std::size_t N_size = std::size(base) / NThread;
	std::size_t left = 0;
	std::size_t right = left + N_size;

	for (auto i = 0U; i < NThread - 1; i++)
	{
		threads.push_back(std::thread(FindDNA, std::ref(base), std::ref(find), left, right, std::ref(vector)));
		left = right;
		right = right + N_size;
	}

	FindDNA(std::ref(base), std::ref(find), left, std::size(base), vector);

	for (auto i = 0U; i < NThread - 1; i++)
	{
		threads[i].join();
	}
}


int main()
{
	std::string base = "AAAAAAAACCCTTTCTTTTCCCCACACACACAGAGAGTCTCTCAAAAGGGGTTTCCCCCCCCAAAAGGGGTTTTAAAAGGGGTTCC";

	std::string find;
	std::cin >> find;

	std::vector <std::size_t> vector;

	MultyFindDNA(base, find, vector);

	for (auto elements : vector)
	{
		for (auto n = 0U; n < std::size(find); n++)
		{
				std::cout << base[elements + n];
		}
		std::cout << std::endl;
	}

	return EXIT_SUCCESS;
}
