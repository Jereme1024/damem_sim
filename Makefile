CC = g++ -std=c++11
CXXFLAGS = -O2

all: matrix_transpose.cpp
	$(CC) matrix_transpose.cpp -o matrix_transpose $(CXXFLAGS)

prof: matrix_transpose.cpp
	$(CC) -pg matrix_transpose.cpp -o matrix_transpose $(CXXFLAGS)


