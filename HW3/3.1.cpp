#include <iostream>
#include <set>
#include <chrono>
#include <vector>
#include <algorithm>
#include <array>

class Timer
{
private:

	using clock_t = std::chrono::steady_clock;
	using time_point_t = clock_t::time_point;
	using duration = clock_t::duration;

public:
	Timer(const std::string& name, std::ostream& stream = std::cout) :
		m_name(name), m_stream(stream), m_begin(clock_t::now()), m_time(duration::zero()), m_running(true) {}

	~Timer() noexcept
	{
		try
		{
			pause();
			m_stream << m_name << " counted " << std::chrono::duration_cast <std::chrono::microseconds> (m_time).count() << " microseconds\n";
		}
		catch (...)
		{
			// std::abort();
		}
	}

	void pause()
	{
		if (m_running)
		{
			m_time = m_time + clock_t::now() - m_begin;
			m_running = false;
		}
	}

	void proceed()
	{
		if (!m_running)
		{
			m_begin = clock_t::now();
			m_running = true;
		}
	}


	int Calculus()
	{
		bool b = m_running;
		pause();
		auto time = std::chrono::duration_cast <std::chrono::microseconds>(m_time).count();
		if (b)
		{
			proceed();
		}
		return time;
	}

private:

	const std::string m_name;
	time_point_t m_begin;
	duration m_time;
	bool m_running;

private:

	std::ostream& m_stream;
};


struct Result
{

	Result() = default;
	Result(const std::string& name, int time) : m_container(name), m_time(time), m_place(0) {}

	Result(Result& other) = default;
	Result(Result&& other) = default;

	Result& operator=(Result& other) = default;
	Result& operator=(Result&& other) = default;

	~Result() = default;

	std::string m_container;
	int m_time;
	int m_place;
};


int main()
{
	std::set <int> st;
	std::cout << "Добавление случайных чисел" << std::endl;
	for (int i = 0; i < 10; i++)
	{
		int random = rand() % 10 + 1;
		st.insert(random);
		std::cout << i + 1 << ")" << random << std::endl;
	}

	const int n = 10;
	std::vector <int> vector(n);
	std::generate(vector.begin(), vector.end(), std::rand);
	std::sort(vector.begin(), vector.end());
	for (int n : vector)
		std::cout << n << std::endl;

	std::array <int, n> array;
	for (int i = 0; i < 100; i++)
	{
		int array = rand() % 1000;
		std::cout << array << std::endl;
 	}
	

	std::vector<Result> v;

	{
		Timer timer_array("Timer for array");
		std::sort(array.begin(), array.end());
		timer_array.pause();
		v.push_back(Result("array", timer_array.Calculus()));
	}


	{
		Timer timer_vector("Timer for vector");
		std::sort(vector.begin(), vector.end());
		timer_vector.pause();
		v.push_back(Result("vector", timer_vector.Calculus()));
	}



}