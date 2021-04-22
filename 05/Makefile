CC=g++
FLAGS=-std=c++17 -Wall -Werror -Wextra -Wno-unused-variable -fsanitize=address
all: test

test: main.o my_serializer.o
	$(CC) $(FLAGS) -o test main.o my_serializer.o
	./test

main.o: main.cpp my_serializer.h
	$(CC) $(FLAGS) -c main.cpp

my_serializer.o: my_serializer.cpp my_serializer.h
	$(CC) $(FLAGS) -c my_serializer.cpp
clean:
	rm -rf *.o test
