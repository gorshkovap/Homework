#define _CRT_SECURE_NO_WARNINGS
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>

template <typename TP>
std::time_t to_time_t(TP tp)
{
	using namespace std::chrono;
	auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
		+ system_clock::now());
	return system_clock::to_time_t(sctp);
}


void view_directory(const std::filesystem::path& path)
{
	if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
	{
		std::cout << "File name" << "Extension" << "Last change time\n";
		for (const auto& entry : std::filesystem::directory_iterator(path))
		{
			auto file_name = entry.path().filename().string();
			auto extension = entry.path().extension().string();
			auto time_point = to_time_t(std::filesystem::last_write_time(path));
			auto last_change_time = std::asctime(std::localtime(&time_point));

			std::cout << file_name << extension << last_change_time;
		}
	}
	else
	{
		std::cout << "Invalid directory\n";
	}
}

int main()
{
	system("chcp 1251");

	std::filesystem::path path;

	std::cin >> path;
	view_directory(path);

	return 0;
}
