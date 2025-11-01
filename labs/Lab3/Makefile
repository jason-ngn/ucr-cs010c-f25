CXX = g++
CXXFLAGS = -std=c++17 -Wall -I/usr/include/gtest -pthread
TARGET = test_list_doubly_linked
SRC = test_list_doubly_linked.cc

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -lgtest -lgtest_main -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
