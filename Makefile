CC = gcc
CFLAGS = -Wall -Wextra -I./include
TARGET = monitor
SRC = src/monitor.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET) $(DIR)