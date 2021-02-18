 #include "2.2 Header.hpp"
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

		std::vector<Result> v;
		
		{
			Timer timer_array("Timer for array");
			std::sort(array.begin(), array.end());
			timer_array.pause();
			v.push_back(Result( "array", timer_array.Calculus() ));
		}
		
		{
			Timer timer_list("Timer for list");
			list.sort();
			timer_list.pause();
			v.push_back(Result( "list", timer_list.Calculus() ));
		}

		
		{
			Timer timer_forward_list("Timer for forward_list");
			forward_list.sort();
			timer_forward_list.pause();
			v.push_back(Result( "forward_list", timer_forward_list.Calculus() ));
		}

		
		{
			Timer timer_vector("Timer for vector");
			std::sort(vector.begin(), vector.end());
			timer_vector.pause();
			v.push_back(Result( "vector", timer_vector.Calculus()));
		}

		
		{
			Timer timer_deque("Timer for deque");
			std::sort(deque.begin(), deque.end());
			timer_deque.pause();
			v.push_back(Result ( "deque", timer_deque.Calculus() ));
		}

		std::sort(v.begin(), v.end(), [](Result& t1, Result& t2) {return t1.m_time < t2.m_time; });

		for (auto i = 0; i < v.size(); ++i) {
			v[i].m_place = i + 1;
			std::cout << v[i].m_container <<' '<< v[i].m_place <<' '<< v[i].m_time << std::endl;
		}
}
