CC=g++
FLAGS=-std=c++17 -Wall -Werror -Wextra -Wno-unused-variable
all: test

test: main.o class.o
	$(CC) $(FLAGS) -o test main.o class.o

main.o: main.cpp class.h
	$(CC) $(FLAGS) -c main.cpp

class.o: class.cpp class.h
	$(CC) $(FLAGS) -c class.cpp
clean:
	rm -rf *.o test
