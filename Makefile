CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

SRC = main.cpp Vector/Vector.cpp
OUT = main

build:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

run: build
	./$(OUT)

clean:
	rm -f $(OUT)
