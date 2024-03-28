CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

complex: 
	$(CXX) matrix.cpp complex.cpp main.cpp -o complex

SOURCES = parse.cpp matrix.cpp complex.cpp

EXECUTABLE = parse

# Default target
# all: $(EXECUTABLE)

# Link source files to create executable
$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXECUTABLE)

# Clean up executable
clean:
	rm -f $(EXECUTABLE)
