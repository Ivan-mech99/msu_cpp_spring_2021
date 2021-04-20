
CC=g++
FLAGS=-std=c++17 -Wall -Werror -Wextra -Wno-unused-variable -fsanitize=address
all: test

test: main.o my_parser.o
	$(CC) $(FLAGS) -o test main.o my_parser.o
	./test

main.o: main.cpp my_parser.h
	$(CC) $(FLAGS) -c main.cpp

my_parser.o: my_parser.cpp my_parser.h
	$(CC) $(FLAGS) -c my_parser.cpp
clean:
	rm -rf *.o test