CC=g++

# problem1A_o: problem1A.cpp
# 	$(CC) -c problem1A.cpp

all: problem1A_ex problem1B_ex

problem1A_ex: problem1A.o
	$(CC) -lrt -fopenmp -o p1a problem1A.cpp

problem1B_ex: problem1B.o
	$(CC) -lrt -fopenmp -o p1b problem1B.cpp

.PHONY: clean

clean:
