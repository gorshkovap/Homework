#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <array>
#include <chrono>
#include <iomanip>
#include <deque>
#include <list>
#include <forward_list>

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
		
		return std::chrono::duration_cast <std::chrono::microseconds> (m_time).count();
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
	const int n = 10000;
	std::array <int, n> array;
	
	std::vector<int> vector(n);

	std::deque <int> deque(n);

	std::list <int> list;

	std::forward_list <int> forward_list;



		for (auto i = 0; i < n; ++i)
		{
			vector[i] = n - i;
			array[i] = n - i;
			deque[i] = n - i;
			list.push_back(n - i);
			forward_list.insert_after(forward_list.before_begin(), i + 1);
		}

		int a;
		{
			Timer timer_array("Timer for array");
			std::sort(array.begin(), array.end());
			a = timer_array.Calculus();
		}
		int b;
		{
			Timer timer_list("Timer for list");
			list.sort();
			b = timer_list.Calculus();
		}

		int c;
		{
			Timer timer_forward_list("Timer for forward_list");
			forward_list.sort();
			c = timer_forward_list.Calculus();
		}

		int d;
		{
			Timer timer_vector("Timer for vector");
			std::sort(vector.begin(), vector.end());
			d = timer_vector.Calculus();
		}

		int e;
		{
			Timer timer_deque("Timer for deque");
			std::sort(deque.begin(), deque.end());
			c = timer_deque.Calculus();
		}

		/*struct Timer_result {
			int a, b, c, d, e;
		};
		
		auto с_time = [](Timer_result& t1, Timer_result& t2) {
			return t1.m_time < t2.m_time;
			};       

		std::sort(Timer_result.begin(), Timer_result.end(), auto c_time);

}*/
