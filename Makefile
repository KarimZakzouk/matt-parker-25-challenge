# Makefile for Matt Parker's 5-Word Alphabet Challenge

CXX = g++
CXXFLAGS = -O2 -std=c++17 -pthread
TARGET = solution
SRC = solution.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
