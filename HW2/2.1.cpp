#include <iostream>
#include <vector>
#include <string>

int main() {
	const int n = 152999999; // вылезает ошибка о нехватке памяти
	std::vector<int> vector(n);
	std::cout << "capacity(): " << vector.capacity() << std::endl;

	std::vector <std::string> sentence;
	sentence.push_back("Hello");
	sentence.insert(sentence.end(), ("How", "are", "you?"));
	std::cout << "max_size(): " << sentence.max_size() << std::endl;
	std::cout << "size(): " << sentence.size() << std::endl;
	std::cout << "capacity(): " << sentence.capacity() << std::endl;
	sentence.reserve(6);
	sentence.insert(find(sentence.begin(), sentence.end(), "you?"), "always or not");
	sentence.insert(sentence.begin(), ("There", "is", "a coomon text"));
	sentence.back() = "!";
	std::cout << "size(): " << sentence.size() << std::endl;
	std::cout << "capacity(): " << sentence.capacity() << std::endl;
}
