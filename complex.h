#ifndef COMPLEX_H

#include <iostream>

class Complex
{
private:
    float r;
    float i;

    Complex split(std::string); // converts string to complex number
                                // have to import libs to return multiple vals
                                // so returning the object itself

public:
    std::string format(); // converts complex number to string

    Complex();

    Complex(float, float); // constructor 1

    Complex(std::string); // constructor 2 for ease

    Complex operator+(Complex&);
    
    Complex operator-(Complex&);

    Complex operator*(Complex&);

    void print();
};

#endif // !COMPLEX_H
