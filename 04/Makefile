CC=g++
FLAGS=-std=c++17 -Wall -Werror -Wextra -Wno-unused-variable -fsanitize=address
all: test

test: main.o my_BigInt.o
	$(CC) $(FLAGS) -o test main.o my_BigInt.o
	./test

main.o: main.cpp my_BigInt.h
	$(CC) $(FLAGS) -c main.cpp

my_BigInt.o: my_BigInt.cpp my_BigInt.h
	$(CC) $(FLAGS) -c my_BigInt.cpp
clean:
	rm -rf *.o test
