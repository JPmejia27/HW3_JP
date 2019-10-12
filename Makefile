CC=g++

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

# problem1A: problem1A.o
# 	$(CC) -o problem1A problem1A.o
#
# problem1B: problem1B.o
# 	$(CC) -o problem1B problem1B.o

pa1: p1_serialC++.o
	$(CC) -o p1_serialC++ p1_serialC++.o

.PHONY: clean

clean:
