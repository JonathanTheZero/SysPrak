CFLAGS = -g -Wall -std=c99
CC = gcc
TARGET = checkPrime.out
# Source files (include all .c files in the current directory)
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)


all: $(TARGET)

.PHONY: clean full run all

# Link the executable from object files
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lm -lpthread

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean up generated files
clean:
	rm -f $(TARGET) $(OBJS)

# Run the program with parameters
run: $(TARGET)
	./$(TARGET)

full:
	make && make run