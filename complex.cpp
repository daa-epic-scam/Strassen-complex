#include <iostream>
#include <string>
#include "complex.h"
using namespace std;

Complex Complex::split(string cnum)
{
    float real = stof(cnum); // PLACEHOLDER
    float im = stof(cnum);
    return Complex(real, im);
}

string Complex::format()
{
    return to_string(this->r) + " + " + to_string(this->i) + "i";
}

Complex::Complex()
{
    this->r = 0;
    this->i = 0;
}

Complex::Complex(float r, float i)
{
    this->r = r;
    this->i = i;
}

Complex::Complex(string cnum)
{
    Complex c = split(cnum);
    this->r = c.r;
    this->i = c.i;
}

Complex Complex::operator+(Complex &addend)
{
    return Complex(this->r + addend.r, this->i + addend.i);
}

Complex Complex::operator-(Complex &subtrahend)
{
    return Complex(this->r - subtrahend.r, this->i - subtrahend.i);
}

Complex Complex::operator*(Complex &factor)
{
    return Complex(this->r * factor.r - this->i * factor.i, this->i * factor.r + this->r * factor.i);
}

void Complex::print()
{
    cout << this->format() << endl;
}
