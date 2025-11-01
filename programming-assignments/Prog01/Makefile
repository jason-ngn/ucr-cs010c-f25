CXX = g++
CXXFLAGS = -Wall -Werror -std=c++11
TARGET = sighting_search
SRC = sighting_search.cc

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) *.o *.out *.txt *.dat
