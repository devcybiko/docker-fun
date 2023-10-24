# Makefile for Hello World program
CC = gcc
CFLAGS = -Wall
TARGET = psil_test
OBJECTS = psil_memory.o

all: $(TARGET) $(OBJECTS)

psil_memory.o: ../psil_memory.c ../psil_memory.h
	$(CC) $(CFLAGS) -c ../psil_memory.c
	
$(TARGET): $(TARGET).c $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(OBJECTS)

clean:
	rm -f $(TARGET)
