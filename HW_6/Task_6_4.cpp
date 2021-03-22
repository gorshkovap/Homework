#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "json.hpp"

using nlohmann::json;

struct Address
{
	std::string street;
	std::string city;
	int postalCode = 0;
	friend std::istream& operator>> (std::istream& in, Address& adress);
};

struct Human
{
	std::string firstName;
	std::string lastName;
	std::size_t age = 0;
	Address address;
	std::vector <std::string> numbers;
	//friend std::ostream& operator<<(std::ostream& stream, const Human& human);
	friend std::istream& operator>> (std::istream& in, Human& human);
};

json struct_to_json(Human& human);

int main()
{
	auto path = std::filesystem::current_path();
	std::filesystem::create_directory(path / "Pearsons");

	std::filesystem::path path_output_1 = path / "Pearsons/6_4 output_1.txt";
	std::filesystem::path path_output_2 = path / "Pearsons/6_4 output_2.txt";

	Human pearson_1;
	Human pearson_2;

	std::cout << "Enter first prearson: " << std::endl;
	std::cin >> pearson_1;
	std::cout << "Enter second prearson: " << std::endl;
	std::cin >> pearson_2;

	json j1 = struct_to_json(pearson_1);
	json j2 = struct_to_json(pearson_1);

	std::fstream fout_1(path_output_1.string(), std::ios::out);
	std::fstream fout_2(path_output_2.string(), std::ios::out);

	fout_1 << std::setw(4) << j1;
	fout_2 << std::setw(4) << j2;

	return EXIT_SUCCESS;
}

json struct_to_json(Human& human)
{
	json j;
	j["firstName"] = human.firstName;
	j["lastName"] = human.lastName;
	j["Age"] = human.age;
	j["address"]["Street"] = human.address.street;
	j["address"]["City"] = human.address.city;
	j["address"]["postCode"] = human.address.postalCode;
	for (auto i = 0; i < std::size(human.numbers); i++)
	{
		j["PhoneNumbers"][i] = human.numbers[i];
	}
	return j;
}

std::istream& operator>>(std::istream& in, Address& adress)
{
	in >> adress.street;
	in >> adress.city;
	in >> adress.postalCode;

	return in;
}

std::istream& operator>>(std::istream& in, Human& human)
{
	in >> human.firstName;
	in >> human.lastName;
	in >> human.age;
	in >> human.address.street;
	in >> human.address.city;
	in >> human.address.postalCode;
	std::string a;
	for (auto i = 0U; std::cin >> a && a != "next"; i++)
	{
		human.numbers.push_back(a);
	}

	return in;
}

//std::ostream& operator<<(std::ostream& stream, const Human& human)
//{
//	std::cout << "firstName: " << human.firstName << std::endl
//		<< "lastName: " << human.lastName << std::endl
//		<< "Age: " << human.age << std::endl
//		<< "Adress: {" << std::endl
//		<< '\t' << "streetAddress: " << human.address.street << std::endl
//		<< '\t' << "City: " << human.address.city << std::endl
//		<< '\t' << "postalCode: " << human.address.postalCode << std::endl << "}" << std::endl
//		<< "Numbers: [" << std::endl; 
//	for (auto element : human.numbers)
//		std::cout << '\t' << element << std::endl;
//	std::cout << "]" << std::endl;
//	return stream;
//}