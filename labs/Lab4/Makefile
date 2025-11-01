CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror
GTEST_FLAGS = -lgtest -lgtest_main -pthread

all: q1-1 q1-2 q2 test_lab_4

q1-1: q1-1.cc stack_vector.h
	$(CXX) $(CXXFLAGS) q1-1.cc -o q1-1

q1-2: q1-2.cc stack_vector.h
	$(CXX) $(CXXFLAGS) q1-2.cc -o q1-2

q2: q2.cc stack_vector.h
	$(CXX) $(CXXFLAGS) q2.cc -o q2

test_lab_4: test_lab_4.cc stack_vector.h q1-1.cc q1-2.cc q2.cc
	$(CXX) $(CXXFLAGS) test_lab_4.cc q1-1.cc q1-2.cc q2.cc $(GTEST_FLAGS) -o test_lab_4

clean:
	rm -f q1-1 q1-2 q2 test_lab_4

.PHONY: all clean