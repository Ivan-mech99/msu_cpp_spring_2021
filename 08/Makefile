CC=g++
FLAGS=-std=c++17 -Wall -Werror -Wextra -Wno-unused-variable -fsanitize=address
all: test

test: main.o my_pool.o
	$(CC) $(FLAGS) -o test main.o my_pool.o
	./test

main.o: main.cpp my_pool.h
	$(CC) $(FLAGS) -c main.cpp

my_pool.o: my_pool.cpp my_pool.h
	$(CC) $(FLAGS) -c my_pool.cpp
clean:
	rm -rf *.o test