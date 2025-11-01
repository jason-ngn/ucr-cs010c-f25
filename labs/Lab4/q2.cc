#include <iostream>
// You can only use stack_vector.h to implement this queue
#include "stack_vector.h"

using namespace std;

template <typename T>
class Queue
{
private:
	// TODO: Define private members for your queue
	Stack<T> s1;
	Stack<T> s2;

public:
	// The time complexity is O(1)
	void Push(const T &item)
	{
		// TODO: Push to the queue
		s1.Push(item);
	}

	// The time complexity is O(n)
	T Pop()
	{
		// TODO: Pop from the queue
		if (s1.Size() == 0 && s2.Size() == 0)
			throw underflow_error("Queue is empty");

		if (s2.Size() == 0)
		{
			while (s1.Size() > 0)
			{
				T temp = s1.Top();
				s1.Pop();
				s2.Push(temp);
			}
		}

		T front = s2.Top();
		s2.Pop();
		return front;
	}

	// The time complexity is O(1)
	size_t Size()
	{
		// TODO: Return the size of the queue
		return s1.Size() + s2.Size();
	}
};

#ifndef NO_MAIN // Only compile main if NO_MAIN is not defined
int main()
{
	Queue<int> q1;

	std::vector<int> v{59, 24, 49, 63, 41};
	for (auto i : v)
	{
		q1.Push(i);
	}
	// print q1
	while (q1.Size() != 0)
	{
		std::cout << q1.Pop() << ", ";
	}
	std::cout << std::endl;

	return 0;
}
#endif
