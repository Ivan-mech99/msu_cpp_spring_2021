CC=g++
FLAGS=-std=c++17 -Wall -Werror -Wextra -Wno-unused-variable -fsanitize=address
all: test

test: main.o my_matrix.o
	$(CC) $(FLAGS) -o test main.o my_matrix.o
	./test

main.o: main.cpp my_matrix.h
	$(CC) $(FLAGS) -c main.cpp

my_allocator.o: my_matrix.cpp my_matrix.h
	$(CC) $(FLAGS) -c my_matrix.cpp
clean:
	rm -rf *.o test
