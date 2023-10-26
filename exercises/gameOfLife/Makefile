CFLAGS = -g -Wall -std=c99
CC = gcc
TARGET = gameOfLife.out
# Source files (include all .c files in the current directory)
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)


all: $(TARGET)

# Link the executable from object files
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean up generated files
clean:
	rm -f $(TARGET) $(OBJS)

# Run the program with parameters
run: $(TARGET)
	./$(TARGET) -s $(s) -p $(p)

s?=16
p?=50
full:
	make && make run s=$(s) p=$(p)