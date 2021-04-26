CC=g++
FLAGS=-std=c++17 -Wall -Werror -Wextra -Wno-unused-variable -fsanitize=address
all: test

test: main.o
	$(CC) $(FLAGS) -o test main.o
	./test

main.o: main.cpp my_format.h
	$(CC) $(FLAGS) -c main.cpp
clean:
	rm -rf *.o test
