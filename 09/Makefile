CC=g++
FLAGS=-std=c++17 -Wall -Werror -Wextra -Wno-unused-variable -fsanitize=address
all: test

test: main.o my_filesort.o
	$(CC) $(FLAGS) -o test main.o my_filesort.o
	./test

main.o: main.cpp my_filesort.h
	$(CC) $(FLAGS) -c main.cpp

my_filesort.o: my_filesort.cpp my_filesort.h
	$(CC) $(FLAGS) -c my_filesort.cpp
clean:
	rm -rf *.o test