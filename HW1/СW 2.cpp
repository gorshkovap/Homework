#include <list>
#include <iostream>



int main(int argc, char** argv)
{
	std::list <int> l1, l2;
	for (auto i = 1; i < 6; i++)
	{
		l1.push_back(i);
		l2.push_back(i);
	}
	l1.splice(std::next(std::begin(l1), 2), //����� ���	
		l2, // �� ������ ������
		std::next(std::begin(l2), 1), // ������ �����������
		std::prev(std::end(l2), 1)); // ����� ����������� 

	for (auto x : l1)
	{
		std::cout << x << " ";
	}
	std::cout << std::endl;

	for (auto x : l2)
	{
		std::cout << x << " ";
	}
}