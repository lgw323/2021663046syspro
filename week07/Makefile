CC = gcc
CFLAGS = -Wall -Wextra -std=c11
OBJS = main.o copy.o
TARGET = longest_line

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c copy.h
copy.o: copy.c copy.h

clean:
	rm -f $(OBJS) $(TARGET)