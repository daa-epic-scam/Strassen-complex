#include <iostream>
#include <string>
#include "complex.h"
using namespace std;

Complex Complex::split(std::string cnum)
{
    int end = cnum.find("+", 0);
    string real = cnum.substr(0, end);
    string im = cnum.substr(end + 1, cnum.size() - end - 2);
    return Complex(stof(real), stof(im));
}

string Complex::format()
{
    return to_string(this->r) + " + " + to_string(this->i) + "i";
}

Complex::Complex() : r(0), i(0) {}

Complex::Complex(float r, float i) : r(r), i(i) {}

Complex::Complex(std::string cnum)
{
    Complex c = split(cnum);
    this->r = c.r;
    this->i = c.i;
}

Complex Complex::operator+(Complex const &addend)
{
    return Complex(this->r + addend.r, this->i + addend.i);
}

Complex Complex::operator-(Complex const &subtrahend)
{
    return Complex(this->r - subtrahend.r, this->i - subtrahend.i);
}

Complex Complex::operator*(Complex const &factor)
{
    return Complex(((factor.r * (this->r + this->i)) - (this->i * (factor.r + factor.i))), ((factor.r * (this->r + this->i)) - (this->r * (factor.i - factor.r))))
}

void Complex::print()
{
    cout << this->format() << endl;
}
