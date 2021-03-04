#include <random>
#include <iostream>
#include <vector>
#include <Chrono>
#include <iterator>
#include <functional>
#include <algorithm>
#include <numeric>


int main(int argc, char** argv)
{
	[](auto& x) {++x; };

	std::vector<int> v1(10);
	std::iota(v1.begin(), v1.end(), 1);

	std::copy(
		std::istream_iterator < int >(std::cin), // добавили еще несколько чисел в вектор
		std::istream_iterator < int >(),
		std::back_inserter(v1));

	std::cout << "vector: ";
	std::copy(v1.cbegin(), v1.cend(),
		std::ostream_iterator < int >(std::cout, " ")); // решил вывести, чтобы проверить :)


	std::default_random_engine dre;  // случайным образом перемешали и вывели
	std::shuffle(std::begin(v1), std::end(v1), dre);



	std::cout << "unique: "; //без дубликатов 
	std::sort(v1.begin(), v1.end());
	v1.erase(std::unique(v1.begin(), v1.end()), v1.end());
	

	auto result = std::count_if(v1.begin(), v1.end(), [](auto x) {return x % 2 != 0; }); // нечетные 
	std::cout << result << std::endl;
	

	auto result_1 = std::minmax_element(v1.begin(), v1.end()); // min and max valume  
	std::cout << *result_1.first << " " << *result_1.second << std::endl;


	std::for_each(v1.begin(), v1.end(), [](auto x) {return x * x; }); // возводим в квадрат

	std::default_random_engine dre; // создаем новую последовательность
	std::uniform_int_distribution <> uid(1, 10);
	std::vector <int> v2(std::size(v1));
	std::generate(std::begin(v2), std::end(v2), [&]() {return uid(dre); });
	std::for_each(std::begin(v2), std::end(v2), [](auto x) {std::cout << x << std::endl; });



	std::cout << std::accumulate(std::begin(v2), std::end(v2), 10) << std::endl; // сумма



	std::fill_n(v2.begin(), 3, 1); // замена чисел
	

	std::vector <int> v3(std::size(v1)); // создание последовательности путем разности
	std::transform(v1.begin(), v1.end(), v2.end(), v3.end(), [](auto a, auto b)
		{
			return std::minus<int>()(a, b); });


	std::replace_if(v3.begin(), v3.end(), [](auto x) {return x < 0; }, 0); //замена отрицательного числа


	v3.erase(std::remove(v3.begin(), v3.end(), 0), v3.end()); // удалили нулевые эл-ты

	std::reverse(v3.begin(), v3.end()); // меняем порядок

	if (v3.size() >= 3) // топ 3 наибольших элемента
	{
		std::nth_element(v3.begin(), v3.end() - 3, v3.end());
		std::cout << "Max three elements: ";
		for (auto a = (v3.end()) - 3; a < v3.end(); a++)
		{
			std::cout << *a << ", ";
		}
		std::cout << std::endl;
	}

	std::sort(v1.begin(), v1.end()); // сортируем по возрастанию
	std::sort(v2.begin(), v2.end());

	std::vector <int> v4;
	std::vector<int> vector_4(v1.size() + v2.size()); // создали последовательность V4
	std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v4.begin());

	auto a = std::equal_range(v4.begin(), v4.end(), 1); // диапазон


	std::copy(v1.begin(), v1.end(), std::ostream_iterator<int>{std::cout, " "}); // Вывод
	std::cout << std::endl;
	std::copy(v2.begin(), v2.end(), std::ostream_iterator<int>{std::cout, " "});
	std::cout << std::endl;
	std::copy(v3.begin(), v3.end(), std::ostream_iterator<int>{std::cout, " "});
	std::cout << std::endl;
	std::copy(v4.begin(), v4.end(), std::ostream_iterator<int>{std::cout, " "});
	std::cout << std::endl;

}

