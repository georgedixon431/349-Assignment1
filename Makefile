CC = gcc
CFLAGS = -Wall -Wextra -std=gnu11 -pthread

TARGET = assignment1

OBJS = main.o input.o criclist.o sort.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c criclist.h input.h
	$(CC) $(CFLAGS) -c main.c

input.o: input.c input.h criclist.h
	$(CC) $(CFLAGS) -c input.c

criclist.o: criclist.c criclist.h
	$(CC) $(CFLAGS) -c criclist.c

sort.o: sort.c sort.h criclist.h
	$(CC) $(CFLAGS) -c sort.c

clean:
	rm -f $(OBJS) $(TARGET)