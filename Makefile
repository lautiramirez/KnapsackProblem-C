CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -g
VALGRINDFLAGS = --show-reachable=yes --leak-check=full
TARGET = knapsack
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

all: $(SOURCES)
	$(CC) $(CFLAGS) -c $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
	
clean: 
	rm -f $(TARGET) $(OBJECTS)

valgrind: $(TARGET)
	valgrind $(VALGRINDFLAGS) ./$(TARGET) -ds -f input/random-500.in -t
	



