# Compiler and flags
CC = g++
CFLAGS = -Wall -Wextra -O2

# Source and executable
SRC = main.cpp
EXECUTABLE = myapp

# Default target
all: $(EXECUTABLE)

# Build the executable
$(EXECUTABLE): $(SRC)
    $(CC) $(CFLAGS) $(SRC) -o $(EXECUTABLE)

# Clean build artifacts
clean:
    del $(EXECUTABLE)

.PHONY: all clean