#include <gtest/gtest.h>
#include "stack_vector.h"
#define NO_MAIN // This prevents main() from being included
#include "q1-1.cc"
#include "q1-2.cc"
#include "q2.cc"
#undef NO_MAIN

// Test Suite Example for Q1.1
TEST(StackSortTest, BasicSort)
{
	Stack<int> s;
	s.Push(3);
	s.Push(1);
	s.Push(2);

	Stack<int> sorted = Sort(s);

	EXPECT_EQ(sorted.Top(), 1); // Smallest on top
	sorted.Pop();
	EXPECT_EQ(sorted.Top(), 2);
	// Add more assertions...
}

TEST(StackSortTest, EmptyStack)
{
	Stack<int> s;
	Stack<int> sorted = Sort(s);
	EXPECT_EQ(sorted.Size(), 0);
}

TEST(StackSortTest, SingleElement)
{
	Stack<int> s;
	s.Push(42);
	Stack<int> sorted = Sort(s);
	EXPECT_EQ(sorted.Size(), 1);
	EXPECT_EQ(sorted.Top(), 42);
}

TEST(StackSortTest, AlreadySorted)
{
	Stack<int> s;
	s.Push(1);
	s.Push(2);
	s.Push(3);
	Stack<int> sorted = Sort(s);
	EXPECT_EQ(sorted.Top(), 1);
	sorted.Pop();
	EXPECT_EQ(sorted.Top(), 2);
	sorted.Pop();
	EXPECT_EQ(sorted.Top(), 3);
}

TEST(StackSortTest, ReverseSorted)
{
	Stack<int> s;
	s.Push(5);
	s.Push(4);
	s.Push(3);
	s.Push(2);
	s.Push(1);
	Stack<int> sorted = Sort(s);
	EXPECT_EQ(sorted.Top(), 1);
	sorted.Pop();
	EXPECT_EQ(sorted.Top(), 2);
	sorted.Pop();
	EXPECT_EQ(sorted.Top(), 3);
	sorted.Pop();
	EXPECT_EQ(sorted.Top(), 4);
	sorted.Pop();
	EXPECT_EQ(sorted.Top(), 5);
}

TEST(StackSortTest, WithDuplicates)
{
	Stack<int> s;
	s.Push(3);
	s.Push(1);
	s.Push(3);
	s.Push(2);
	s.Push(1);
	Stack<int> sorted = Sort(s);
	EXPECT_EQ(sorted.Top(), 1);
	sorted.Pop();
	EXPECT_EQ(sorted.Top(), 1);
	sorted.Pop();
	EXPECT_EQ(sorted.Top(), 2);
	sorted.Pop();
	EXPECT_EQ(sorted.Top(), 3);
	sorted.Pop();
	EXPECT_EQ(sorted.Top(), 3);
}

TEST(StackSortTest, LargeRandomValues)
{
	Stack<int> s;
	std::vector<int> values = {59, 12, 44, 99, 23, 67, 8, 45};
	for (int v : values)
		s.Push(v);
	Stack<int> sorted = Sort(s);
	int prev = -1;
	while (sorted.Size() > 0)
	{
		int curr = sorted.Top();
		sorted.Pop();
		EXPECT_GE(curr, prev);
		prev = curr;
	}
}

TEST(DeleteMiddleTest, OddSize_RemoveMiddle)
{
	Stack<int> s;
	std::vector<int> v = {1, 2, 3, 4, 5};
	for (int x : v)
		s.Push(x);
	size_t n = s.Size();
	DeleteMiddleElement(s, n);

	std::vector<int> expected = {5, 4, 2, 1};
	for (int i = 0; i < expected.size(); ++i)
	{
		ASSERT_GT(s.Size(), 0);
		EXPECT_EQ(s.Top(), expected[i]);
		s.Pop();
	}
	EXPECT_EQ(s.Size(), 0);
}

TEST(DeleteMiddleTest, EvenSize_RemoveMiddle)
{
	Stack<int> s;
	std::vector<int> v = {1, 2, 3, 4};
	for (int x : v)
		s.Push(x);
	size_t n = s.Size();
	DeleteMiddleElement(s, n);

	std::vector<int> expected = {4, 2, 1};
	for (int val : expected)
	{
		ASSERT_GT(s.Size(), 0);
		EXPECT_EQ(s.Top(), val);
		s.Pop();
	}
	EXPECT_EQ(s.Size(), 0);
}

TEST(DeleteMiddleTest, SingleElement)
{
	Stack<int> s;
	s.Push(100);
	DeleteMiddleElement(s, s.Size());
	EXPECT_EQ(s.Size(), 0);
}

TEST(DeleteMiddleTest, EmptyStack)
{
	Stack<int> s;
	EXPECT_NO_THROW(DeleteMiddleElement(s, 0));
	EXPECT_EQ(s.Size(), 0);
}

TEST(DeleteMiddleTest, MultipleCallsOnSameStack)
{
	Stack<int> s;
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	s.Push(5);
	size_t n = s.Size();
	DeleteMiddleElement(s, n);

	n = s.Size();
	DeleteMiddleElement(s, n);

	std::vector<int> expected = {5, 2, 1};
	for (int val : expected)
	{
		ASSERT_GT(s.Size(), 0);
		EXPECT_EQ(s.Top(), val);
		s.Pop();
	}
}

TEST(QueueTest, FIFO_BasicOrder)
{
	Queue<int> q;
	std::vector<int> input = {10, 20, 30, 40};
	for (int x : input)
		q.Push(x);

	for (int i = 0; i < input.size(); ++i)
	{
		ASSERT_GT(q.Size(), 0);
		EXPECT_EQ(q.Pop(), input[i]);
	}
	EXPECT_EQ(q.Size(), 0);
}

TEST(QueueTest, EmptyQueuePop_Throws)
{
	Queue<int> q;
	EXPECT_THROW(q.Pop(), std::underflow_error);
}

TEST(QueueTest, SizeAfterPushAndPop)
{
	Queue<int> q;
	EXPECT_EQ(q.Size(), 0);

	q.Push(1);
	q.Push(2);
	EXPECT_EQ(q.Size(), 2);

	q.Pop();
	EXPECT_EQ(q.Size(), 1);

	q.Pop();
	EXPECT_EQ(q.Size(), 0);
}

TEST(QueueTest, AlternatingPushPop)
{
	Queue<int> q;
	q.Push(1);
	EXPECT_EQ(q.Pop(), 1);

	q.Push(2);
	q.Push(3);
	EXPECT_EQ(q.Pop(), 2);

	q.Push(4);
	EXPECT_EQ(q.Pop(), 3);
	EXPECT_EQ(q.Pop(), 4);
}

TEST(QueueTest, LargeSequenceFIFO)
{
	Queue<int> q;
	const int N = 100;
	for (int i = 0; i < N; ++i)
	{
		q.Push(i);
	}
	for (int i = 0; i < N; ++i)
	{
		EXPECT_EQ(q.Pop(), i);
	}
	EXPECT_EQ(q.Size(), 0);
}

TEST(QueueTest, PushAfterPopAll)
{
	Queue<int> q;
	q.Push(5);
	q.Push(6);
	q.Pop();
	q.Pop();
	EXPECT_EQ(q.Size(), 0);

	q.Push(7);
	EXPECT_EQ(q.Pop(), 7);
}

TEST(QueueTest, PopTriggersAmortizedTransfer)
{
	Queue<int> q;
	for (int i = 0; i < 10; ++i)
		q.Push(i);

	EXPECT_EQ(q.Pop(), 0);
	EXPECT_EQ(q.Pop(), 1);

	q.Push(100);
	q.Push(200);

	EXPECT_EQ(q.Pop(), 2);
	EXPECT_EQ(q.Pop(), 3);

	for (int i = 4; i <= 9; ++i)
		q.Pop();
	q.Push(300);

	EXPECT_EQ(q.Pop(), 100);
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
