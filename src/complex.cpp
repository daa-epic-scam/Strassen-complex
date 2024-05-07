#include <iostream>
#include <string>
#include "../include/complex.h"
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
    auto a = this->r;
    auto b = this->i;
    auto c = factor.r;
    auto d = factor.i;
    
    float k1 = (c * (a + b));
    float k2 = (b * (c + d));
    float k3 = (a * (d - c));
    // float k1 = (factor.r * (this->r + this->i));
    // float k2 = (this->i * (factor.r + factor.i));
    // float k3 = (this->r * (factor.i - factor.r));
    return Complex(k1 - k2, k1 + k3);
    // return Complex(this->r * factor.r - this->i * factor.i, this->r * factor.i + this->i + factor.r);
}

void Complex::print()
{
    cout << this->format() << endl;
}
