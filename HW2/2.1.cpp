#include <iostream>
#include <vector>
#include <string>

int main() {
	const int n = 155999999; // вылезает ошибка о нехватке памяти
	std::vector<int> vector(n);
	std::cout << "capacity(): " << vector.capacity() << std::endl;
	try
	{
		if (n > 154999999)
		{
			throw std::overflow_error("too big value");
		}
		std::cout << "capacity:" << vector.capacity() << ' ';
	}
	catch (const std::overflow_error& exception)
	{
		std::cerr << "Error : " << exception.what() << '\n';
	}

	std::vector <std::string> sentence;
	sentence.push_back("Hello");
	sentence.insert(sentence.end(), ("How", "are", "you?"));
	std::cout << "max_size(): " << sentence.max_size() << std::endl;
	std::cout << "size(): " << sentence.size() << std::endl;
	std::cout << "capacity(): " << sentence.capacity() << std::endl;
	sentence.insert(find(sentence.begin(), sentence.end(), "you?"), "always or not");
	sentence.insert(sentence.begin(), ("There", "is", "a coomon text"));
	sentence.back() = "!";
	std::cout << "size(): " << sentence.size() << std::endl;
	std::cout << "capacity(): " << sentence.capacity() << std::endl;

}
