#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>
#include <chrono>
#include <iomanip>
#include <string>

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

class Threads_Guard
{
public:

	explicit Threads_Guard(std::vector < std::thread >& threads) :
		m_threads(threads)
	{}

	Threads_Guard(Threads_Guard const&) = delete;

	Threads_Guard& operator=(Threads_Guard const&) = delete;

	~Threads_Guard() noexcept
	{
		try
		{
			for (std::size_t i = 0; i < m_threads.size(); ++i)
			{
				if (m_threads[i].joinable())
				{
					m_threads[i].join();
				}
			}
		}
		catch (...)
		{
			// std::abort();
		}
	}

private:

	std::vector < std::thread >& m_threads;
};

template < typename Iterator, typename T >
struct accumulate_block
{
	T operator()(Iterator first, Iterator last)
	{
		return std::accumulate(first, last, T());
	}
};

template < typename Iterator, typename T >
T parallel_accumulate(Iterator first, Iterator last, T init, std::size_t num_threads)
{
	const std::size_t length = std::distance(first, last);

	if (!length)
		return init;

	const std::size_t block_size = length / num_threads;

	std::vector < std::future < T > > futures(num_threads - 1);
	std::vector < std::thread >		  threads(num_threads - 1);

	Threads_Guard guard(threads);

	Iterator block_start = first;

	for (std::size_t i = 0; i < (num_threads - 1); ++i)
	{
		Iterator block_end = block_start;
		std::advance(block_end, block_size);

		std::packaged_task < T(Iterator, Iterator) > task{
			accumulate_block < Iterator, T >() };

		futures[i] = task.get_future();
		threads[i] = std::thread(std::move(task), block_start, block_end);

		block_start = block_end;
	}

	T last_result = accumulate_block < Iterator, T >()(block_start, last);

	T result = init;

	for (std::size_t i = 0; i < (num_threads - 1); ++i)
	{
		result += futures[i].get();
	}

	result += last_result;

	return result;
}

int main(int argc, char** argv)
{
	std::vector < int > v(100000);

	std::iota(v.begin(), v.end(), 1);
	Timer timer("Timer");
	auto num_threads = 1U;
	for (; num_threads < 20; ++num_threads)
	{
		auto start = timer.Calculus();
		auto rubbish = parallel_accumulate(v.begin(), v.end(), 0, num_threads);
		auto end = timer.Calculus();
		auto time = end - start;
		std::cout << std::left << std::setw(10) << std::setfill(' ') << num_threads << time << '\n';
	}
	for (; num_threads < 1001; num_threads+=10)
	{
		auto start = timer.Calculus();
		auto rubbish = parallel_accumulate(v.begin(), v.end(), 0, num_threads);
		auto end = timer.Calculus();
		auto time = end - start;
		std::cout << std::left << std::setw(10) << std::setfill(' ') << num_threads << time << '\n';
	}

	system("pause");

	return EXIT_SUCCESS;
}
