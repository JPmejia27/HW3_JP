CC=g++

# problem1A_o: problem1A.cpp
# 	$(CC) -c problem1A.cpp

problem1A_ex: problem1A.o
	$(CC) -lrt -fopenmp -o p1A problem1A.cpp

.PHONY: clean

clean:
