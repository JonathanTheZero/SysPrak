CFLAGS = -g -Wall -std=c99 -wextra
CC = gcc
TARGET = checkPrime.out
# Source files (include all .c files in the current directory)
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

.PHONY: clean full run all

all: $(TARGET)

# Link the executable from object files
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lm -lpthread -lc -lgmp

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
	make
	make run