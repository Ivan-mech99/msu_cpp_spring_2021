
CC=g++
FLAGS=-std=c++17 -Wall -Werror -Wextra -Wno-unused-variable -fsanitize=address
all: test
test: main.o
	$(CC) $(FLAGS) -o test main.o
	./test

main.o: main.cpp My_vector.h
	$(CC) $(FLAGS) -c main.cpp

clean:
	rm -rf *.o test