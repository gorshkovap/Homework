#include <iostream>
#include <vector>
#include <string>

int main() {
	const int n = 1579999; // вылезает ошибка о нехватке памяти
	std::vector<int> vector(n);
	/*try
	{
		if (n > 156999999)
		std::cout << "capacity:" << vector.capacity() << ' ';
	}
	catch (const std::bad_alloc& exception)
	{
		std::cerr << "Error " << exception.what() << std::endl;
		std::cout << vector.capacity() << std::endl;
	}*/


	std::vector<int> v(10, 0);
	std::cout << "number of elements " << v.capacity() << std::endl;  // 10 elements
	v.push_back(0);
	std::cout << "number of elements " << v.capacity() << std::endl;   // 15 elements (1.5 * 10) 

	v.reserve(100);
	std::cout << "Size is " << v.capacity() << std::endl; // 100 elements

	auto N = v.capacity();
	while(true) 
	{
		N *= 10; 
		try
		{
			v.reserve(N);
		}
		catch (const std::exception& exception)
		{
			std::cerr << "Error" << exception.what();
			break;
		}
	}

	std::cout << N / 10 << std::endl;
	std::cout << "Capacity is " << v.capacity(); 
