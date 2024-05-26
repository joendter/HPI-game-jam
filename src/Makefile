# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17

# Output executable name
EXEC = ../out/main

# Find all .cpp files in the current directory
SOURCES = $(wildcard *.cpp)

# Generate object file names by replacing .cpp with .o
OBJECTS = $(SOURCES:.cpp=.o)

# Default target to build the executable
all: mkdir clean unclean 

unclean: $(EXEC)

# Rule to link the object files into the executable
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJECTS) $(EXEC)

mkdir:
	mkdir -p ../out

# Phony targets to avoid conflicts with files named 'all' or 'clean'
.PHONY: all clean
