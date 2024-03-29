CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Source directories
SRCDIR = src
INCDIR = include

# Executable
EXECUTABLE = main

# Source files
SOURCES = $(filter-out src/time.cpp, $(wildcard $(SRCDIR)/*.cpp))

# Header files
HEADERS = $(wildcard $(INCDIR)/*.h)

# Default target
all: $(EXECUTABLE)

# Build executable from source files
$(EXECUTABLE): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) $(SOURCES) -o bin/$(EXECUTABLE)

# Clean up
clean:
	rm -f bin/$(EXECUTABLE)

.PHONY: all clean
