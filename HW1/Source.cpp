#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
class Timer
{
private:

	using clock_t = std::chrono::steady_clock;
	using time_point_t = clock_t::time_point;
	using duration = clock_t::duration;

public:
	Timer(const std::string& name, std::ostream& stream = std::cout) :
		m_name(name), m_stream(stream), m_begin(clock_t::now()), m_time(duration::zero()), m_running(true)  {}

	~Timer() noexcept
	{ 
		try
		{ 
			pause();
			m_stream << m_name << " counted "  << std::chrono::duration_cast <std::chrono::microseconds> (m_time).count() << " microseconds\n";
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
	{
		Timer timer_ac("Timer for a and c");
		std::vector<double> a(100000, 8.5);
		timer_ac.pause();
		Timer timer_b("Timer for b");
		std::vector<double> b(100000, 8.5);
		timer_b.pause();
		timer_ac.proceed();
		std::vector<double> c(100000, 8.5);
	}

	return 0;
}
