#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <execution>
#include <functional>

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

int main()
{
	const std::size_t N = 1000000;

	std::vector <double> in(N, 2.0); // N - кол во элементов
	std::vector <double> out(N, 2.0);
	std::iota(std::begin(in), std::end(in), 1.0);

	auto lambda = [](double a, double b) { return a*b/2; };

	std::cout << "size of vector: " << N << '\n';

	{
		Timer simple_algorithm_time1("simple_algorithm_time1");
		std::sort(std::begin(in), std::end(in), [](auto& x, auto& y) {return x > y; });
	}

	{
		Timer parallel_algorithm_time_1("parallel_algorithm_time_1");
		std::sort(std::execution::par, std::begin(in), std::end(in), [](auto& x, auto& y) {return x > y; });
	}

	{
		Timer simple_algorithm_time2("simple_algorithm_time2");
		std::partial_sum(std::begin(in), std::end(in), std::begin(out), lambda);
	}

	{
		Timer parallel_algorithm_time_2("parallel_algorithm_time_2");
		std::inclusive_scan(std::execution::par, std::begin(in), std::end(in), std::begin(out), lambda);
	}

	{
		Timer simple_algorithm_time3("simple_algorithm_time3");
		std::cout << std::inner_product(std::begin(in), std::end(in), std::begin(out), 1.0) << '\n';
	}

	{
		Timer parallel_algorithm_time_3("parallel_algorithm_time_3");
		std::cout << std::transform_reduce(std::execution::par, std::begin(in), std::end(in), std::begin(out), 1.0) << '\n';
	}

	return 0;
}
