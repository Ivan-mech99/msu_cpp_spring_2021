CC=g++
FLAGS=-std=c++17 -Wall -Werror -Wextra -Wno-unused-variable -fsanitize=address
all: test

test: main.o my_allocator.o
	$(CC) $(FLAGS) -o test main.o my_allocator.o
	./test

main.o: main.cpp my_allocator.h
	$(CC) $(FLAGS) -c main.cpp

my_allocator.o: my_allocator.cpp my_allocator.h
	$(CC) $(FLAGS) -c my_allocator.cpp
clean:
	rm -rf *.o test
