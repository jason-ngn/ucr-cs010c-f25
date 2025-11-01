#include <iostream>

#include "stack_vector.h"

using namespace std;

// The time complexity of this function is O(n^2), and space complexity is O(n)
template <typename T>
Stack<T> Sort(Stack<T> &s1)
{
	// TODO: Sort the stack s1 and return the sorted stack
	Stack<T> tempStack;
	vector<T> tempVect(s1.Size());

	for (int i = 0; i < s1.Size(); i++)
	{
		tempVect.at(i) = s1.Top();
		s1.Pop();
	}

	for (int i = 0; i < tempVect.size(); i++)
	{
		for (int j = 0; j < tempVect.size(); j++)
		{
			if (tempVect.at(i) > tempVect.at(j))
			{
				T temp = tempVect.at(i);
				tempVect.at(i) = tempVect.at(j);
				tempVect.at(j) = temp;
			}
		}
	}

	for (int i = 0; i < tempVect.size(); i++)
	{
		tempStack.Push(tempVect.at(i));
	}

	return tempStack;
}

#ifndef NO_MAIN // Only compile main if NO_MAIN is not defined
int main()
{
	Stack<int> s1;

	std::vector<int> v{44, 12, 59, 41};
	for (auto i : v)
		s1.Push(i);

	// sort
	Stack<int> s2 = Sort(s1);

	// print s2
	while (s2.Size() != 0)
	{
		std::cout << s2.Top() << ", ";
		s2.Pop();
	}
	std::cout << std::endl;

	return 0;
}
#endif
