CXX := g++
CXXFLAGS := -Wall -Werror -std=c++11

all: bt bst

bt: bt.cc bt.h
	$(CXX) $(CXXFLAGS) bt.cc -o bt 

bst: bst.cc bst.h
	$(CXX) $(CXXFLAGS) bst.cc -o bst

clean:
	-rm -f bt bst