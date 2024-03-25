#include <iostream>

class Complex {
private:
    float r;
    float i;

    Complex split(std::string); // converts string to complex number
                                // have to import libs to return multiple vals
                                // so returning the object itself
    
public:
    std::string format(); // converts complex number to string

    Complex(float r, float i); // constructor 1

    Complex(std::string); // constructor 2 for ease
    
    Complex operator+(Complex& addend);
    
    Complex operator*(Complex& addend);

    
    void print();
};
