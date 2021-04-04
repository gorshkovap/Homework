#include <iostream>
#include <future>
#include <cmath>
#include <thread>
#include <random>
#include <chrono>
#include <iomanip>
#include <vector>



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



std::mutex mtx;

void Monte_Carlo(std::size_t N, std::size_t & count)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0, 1.0);

	std::size_t t = 0;
	for (auto i = 0; i < N; ++i)
		if (std::pow(dis(gen), 2) + std::pow(dis(gen), 2) <= 1)
		{
			t++;
		}
	std::lock_guard lg(mtx);
	count += t;
}

double SingleMonteCarlo(std::size_t N)
{
	std::size_t count = 0;
	Monte_Carlo(N, std::ref(count));
	return 4.0 * count / N;
}

double MultyMonteCarlo(std::size_t N)
{
	if (std::thread::hardware_concurrency() <= 1)
	{
		std::cout << "More threads" << std::endl;
		return -1.0;
	}

	std::size_t Nthreads = std::thread::hardware_concurrency();

	std::vector <std::thread> threads;

	std::size_t CountN = N / Nthreads;
	std::size_t count = 0;

	for (auto i = 0U; i < (Nthreads - 1); i++)
		threads.push_back(std::thread(Monte_Carlo, CountN, std::ref(count)));

	Monte_Carlo(CountN, std::ref(count));

	for (auto i = 0U; i < std::size(threads); i++)
		threads[i].join();

	return 4.0 * count / N;
}

int main()
{
	{
		Timer single("Single Thread");

		std::cout << SingleMonteCarlo(314159) << std::endl;
	}

	{
		Timer multy("Multy Thread");

		std::cout << MultyMonteCarlo(314159) << std::endl;
	}

	return EXIT_SUCCESS;
}
