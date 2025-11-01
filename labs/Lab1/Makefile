CXX = g++
CXXFLAGS = -Wall -std=c++11

prog: prog.o A.o B.o
	$(CXX) -o prog prog.o A.o B.o

prog.o: prog.cc A.h B.h
	$(CXX) $(CXXFLAGS) -c prog.cc

A.o: A.cc A.h
	$(CXX) $(CXXFLAGS) -c A.cc

B.o: B.cc B.h
	$(CXX) $(CXXFLAGS) -c B.cc

clean:
	rm -f *.o prog
