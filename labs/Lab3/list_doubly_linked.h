// TODO: include guard
// TODO: What else do you need to include?
#ifndef LIST_DOUBLY_LINKED_H
#define LIST_DOUBLY_LINKED_H

#include <memory>
#include <stdexcept>
#include <cstddef>

using namespace std;

/**
 * Implementation of a List ADT using a doubly linked list data structure with smart pointers.
 *
 * TODO: Study the singly linked list implementation (list_singly_linked.h) for reference.
 * TODO: Design your Node structure to support bidirectional navigation.
 * TODO: Consider using smart pointers for ownership (which direction should own memory?).
 * TODO: Implement all required methods.
 */

// TODO: Q 1.1 Create a templated class ListDoublyLinked
// based on the ListSinglyLinked class studied in class.
// What extra data members do you need for this implementation?
template <typename T>
class ListDoublyLinked
{
private:
	struct Node
	{
		// TODO: Define the node structure
		// Hint: What data does each node need to store?
		// Hint: How should you handle forward vs backward pointers with smart pointers?

		T data;
		unique_ptr<Node> nextPtr;
		Node *prevPtr;

		Node(const T &item) : data(item), nextPtr(nullptr), prevPtr(nullptr) {}
	};

	// TODO: Q 1.2 How would you slightly change this previous data structure to use smart pointers?
	// Explain why it would be a good design in a comment.

	// TODO: Define private data members for your list

	unique_ptr<Node> head;
	Node *tail;
	unsigned int size;

	// TODO: Implement helper method to get node at position
	// Q 1.3 Now implement private method GetNode() which returns a pointer to a node in the list at a given position.
	// Return pointer on node located as position @pos
	Node *GetNode(unsigned int pos)
	{
		if (pos >= size)
		{
			throw out_of_range("GetNode: position out of range");
		}

		if (pos == 0)
			return head.get();
		if (pos == size - 1)
			return tail;

		if (pos <= size / 2)
		{
			Node *curr = head.get();
			for (unsigned int i = 0; i < pos; i++)
				curr = curr->nextPtr.get();

			return curr;
		}
		else
		{
			Node *curr = tail;
			for (unsigned int i = size - 1; i > pos; i--)
				curr = curr->prevPtr;

			return curr;
		}
	}

public:
	// TODO: Q 2.1 Implement a default constructor and destructor.
	ListDoublyLinked() : head(nullptr), tail(nullptr), size(0) {}

	~ListDoublyLinked() = default;

	// TODO: Q 2.2 Implement the Size() method.
	// Return number of items in list
	unsigned int Size()
	{
		return size;
	}

	// TODO: Q 2.3 Implement the Get() method.
	// Return item at position @pos
	const T &Get(const unsigned int pos)
	{
		if (pos >= size)
			throw out_of_range("Get: position out of range");

		return GetNode(pos)->data;
	}

	// TODO: Q 2.4 Implement the Find method.
	// Return position of first occurrence of @item (-1 if not found)
	int Find(const T &item)
	{
		Node *curr = head.get();
		unsigned int index = 0;
		while (curr)
		{
			if (curr->data == item)
				return static_cast<int>(index);
			curr = curr->nextPtr.get();
			index++;
		}
		return -1;
	}

	// TODO: Q 2.5 Discuss the different scenarios for item removal.
	// Using these possible combinations, implement the Restd::move method.
	// Restd::move item at position @pos
	void Remove(const unsigned int pos)
	{
		if (pos >= size)
			throw out_of_range("Restd::move: position out of range");

		if (pos == 0)
		{
			if (head)
			{
				head = std::move(head->nextPtr);
				if (head)
					head->prevPtr = nullptr;
				else
					tail = nullptr;
			}
			size--;
			return;
		}

		Node *prev = GetNode(pos - 1);
		Node *curr = prev->nextPtr.get();

		if (curr == tail)
		{
			prev->nextPtr.reset();
			tail = prev;
			size--;
			return;
		}

		prev->nextPtr = std::move(curr->nextPtr);
		if (prev->nextPtr)
			prev->nextPtr->prevPtr = prev;
		size--;
	}

	// TODO: Q 2.6 Discuss the different scenarios for item insertion.
	// Based on the discussion above, implement the Insert method.
	// Insert @item at position @pos
	void Insert(const T &item, const unsigned int pos)
	{
		if (pos > size)
			throw out_of_range("Insert: position out of range");

		if (pos == 0)
		{
			auto newNode = make_unique<Node>(item);
			newNode->nextPtr = std::move(head);
			newNode->prevPtr = nullptr;
			if (newNode->nextPtr)
				newNode->nextPtr->prevPtr = newNode.get();
			head = std::move(newNode);
			if (size == 0)
				tail = head.get();
			size++;
			return;
		}

		Node *prev = GetNode(pos - 1);
		if (pos == size)
		{
			auto newNode = make_unique<Node>(item);
			newNode->prevPtr = prev;
			prev->nextPtr = std::move(newNode);
			tail = prev->nextPtr.get();
			size++;
			return;
		}

		auto newNode = make_unique<Node>(item);
		newNode->nextPtr = std::move(prev->nextPtr);
		newNode->prevPtr = prev;
		if (newNode->nextPtr)
			newNode->nextPtr->prevPtr = newNode.get();
		prev->nextPtr = std::move(newNode);
		size++;
	}
};

#endif