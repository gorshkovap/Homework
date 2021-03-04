  
#pragma once
#include <iostream>
#include <set>
#include <chrono>
#include <vector>
#include <algorithm>
#include <iomanip>

class Timer
{
private:

	using clock_t = std::chrono::steady_clock;
	using time_point_t = clock_t::time_point;
	using duration = clock_t::duration;

public:
	Timer(const std::string& name, std::ostream& stream = std::cout) :
		m_name(name), m_stream(stream), m_begin(clock_t::now()), m_time(duration::zero()), m_running(true) {}

	~Timer() noexcept {}

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

std::pair <int, int> counter(const int n)
{
	Timer timer_set("timer for set");

	std::set <int> st;
	for (int i = 0; i < n; ++i)
	{
		st.insert(n - i);
	}
	int result_set = timer_set.Calculus();

	Timer timer_vector("Timer for vector");
	std::vector<int> vector(n,0);
	for (int i = 0; i < n; ++i)
	{
		vector[i] = n - i;
	}
	std::sort(vector.begin(), vector.end());
	int result_vector = timer_vector.Calculus();

	return { result_set, result_vector };
}
