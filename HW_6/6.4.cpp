#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "json.hpp"


using nlohmann::json;


struct Work
{
	std::string position;
	unsigned int salary = 0;
	friend std::istream& operator>> (std::istream& in, Work& work);
};


struct Human
{
	std::string firstName;
	std::string lastName;
	std::string condition;
	std::size_t age = 0;
	Work work;
	std::vector <std::string> numbers;
	friend std::istream& operator>> (std::istream& in, Human& human);
};

json struct_to_json(Human& human);

int main()
{
	auto path = std::filesystem::current_path();
	std::filesystem::create_directory(path / "Information");

	std::filesystem::path path_output_1 = path / "Information/6.4 output_1.txt";
	std::filesystem::path path_output_2 = path / "Information/6.4 output_2.txt";

	Human information_1;
	Human information_2;

	std::cout << "Enter first information: " << std::endl;
	std::cin >> information_1;
	std::cout << "Enter the second information: " << std::endl;
	std::cin >> information_2;

	json j1 = struct_to_json(information_1);
	json j2 = struct_to_json(information_1);

	std::fstream fout_1(path_output_1.string(), std::ios::out);
	std::fstream fout_2(path_output_2.string(), std::ios::out);

	return EXIT_SUCCESS;
}

json struct_to_json(Human& human)
{
	json j;
	j["firstName"] = human.firstName;
	j["lastName"] = human.lastName;
	j["Age"] = human.age;
	j["Condition"] = human.condition;
	j["Work"]["post"] = human.work.position;
	j["Work"]["salary"] = human.work.salary;
	return j;
}

std::istream& operator>>(std::istream& in, Work& work)
{
	in >> work.position;
	in >> work.salary;

	return in;
}

std::istream& operator>>(std::istream& in, Human& human)
{
	in >> human.firstName;
	in >> human.lastName;
	in >> human.age;
	in >> human.work.position;
	in >> human.work.salary;

	return in;
}

