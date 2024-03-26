#ifndef COMPLEX_H

#include <iostream>
using namespace std;

class Complex
{
private:
    float r;
    float i;

    Complex split(string); // converts string to complex number
                           // have to import libs to return multiple vals
                           // so returning the object itself

public:
    string format(); // converts complex number to string

    Complex();

    Complex(float, float); // constructor 1

    Complex(string); // constructor 2 for ease

    Complex operator+(Complex const& );
    
    Complex operator-(Complex const&);

    Complex operator*(Complex const&);

    friend ostream &operator<<(ostream &os, const Complex &cnum);

    void print();
};

#endif // !COMPLEX_H
