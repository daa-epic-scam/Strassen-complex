all: complex

complex: 
	g++ matrix.cpp complex.cpp main.cpp -o complex

clean:
	rm complex
