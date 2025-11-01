#include <gtest/gtest.h>
#include "list_doubly_linked.h"

using namespace std;

TEST(List, List)
{
	ListDoublyLinked<int> l;

	// Initially empty
	ASSERT_EQ(l.Size(), 0);

	// Insert at head
	l.Insert(10, 0);
	ASSERT_EQ(l.Size(), 1);
	EXPECT_EQ(l.Get(0), 10);

	// Insert at tail
	l.Insert(20, 1);
	l.Insert(30, 2);
	ASSERT_EQ(l.Size(), 3);
	EXPECT_EQ(l.Get(0), 10);
	EXPECT_EQ(l.Get(1), 20);
	EXPECT_EQ(l.Get(2), 30);

	// Insert in middle
	l.Insert(15, 1);
	ASSERT_EQ(l.Size(), 4);
	EXPECT_EQ(l.Get(1), 15);
	EXPECT_EQ(l.Get(2), 20);

	// Find tests
	EXPECT_EQ(l.Find(10), 0);
	EXPECT_EQ(l.Find(20), 2);
	EXPECT_EQ(l.Find(99), -1);

	// Remove head
	l.Remove(0);
	ASSERT_EQ(l.Size(), 3);
	EXPECT_EQ(l.Get(0), 15);

	// Remove middle
	l.Remove(1);
	ASSERT_EQ(l.Size(), 2);
	EXPECT_EQ(l.Get(1), 30);

	// Remove tail
	l.Remove(1);
	ASSERT_EQ(l.Size(), 1);
	EXPECT_EQ(l.Get(0), 15);

	// Remove last remaining
	l.Remove(0);
	ASSERT_EQ(l.Size(), 0);
}

TEST(List, OutOfRange)
{
	ListDoublyLinked<int> l;
	EXPECT_THROW(l.Get(0), out_of_range);
	EXPECT_THROW(l.Remove(0), out_of_range);
	EXPECT_THROW(l.Insert(1, 1), out_of_range);
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}