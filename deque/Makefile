CC = gcc
CFLAGS = -W -Wall

OBJECTS = proj3B.o proj3B_deque.o
TARGET = proj3B

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

proj3B.o: proj3B.c proj3B_deque.h
	$(CC) $(CFLAGS) -c proj3B.c -o proj3B.o

proj3B_deque.o: proj3B_deque.c proj3B_deque.h
	$(CC) $(CFLAGS) -c proj3B_deque.c -o proj3B_deque.o

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean tarball
