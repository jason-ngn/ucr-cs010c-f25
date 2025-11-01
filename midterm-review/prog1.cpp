#include <iostream>

using namespace std;

template <typename T>
class List
{
public:
	List();
	~List();

	size_t Size();
	const T &Get(const size_t pos);
	int Find(const T &item);
	void Remove(const size_t pos);
	void Insert(const T &item, const size_t pos);
	void MoveToBack(size_t pos)
	{
		if (pos >= cur_size)
			throw out_of_range("Position out of range");

		// Get the tail
		Node *tail = GetNode(cur_size);

		// Get the node from pos
		Node *n = GetNode(pos);

		// Get the node previous to pos
		Node *prev = GetNode(pos - 1);

		prev->next = n->next;
		tail->next = n;
		n->next = nullptr;
	}

private:
	struct Node
	{
		T item;
		Node *next;
	};
	Node *head = nullptr;
	unsigned int cur_size = 0;

	Node *GetNode(const size_t pos)
	{
		if (pos >= cur_size)
			throw out_of_range("Position out of range");

		Node *n = head;
		while (pos--)
			n = n->next;
		return n;
	}
};

template <typename T>
class Stack
{
public:
	Stack();
	~Stack();

	size_t Size();
	T &Top();
	void Pop();
	void Push(const T &item);
};

template <typename T>
class Queue
{
public:
	Queue();
	~Queue();

	size_t Size();
	T &Front();
	void Pop();
	void Push(const T &item);
	void InterleaveHalves()
	{
		Stack<int> temp;
	}
};