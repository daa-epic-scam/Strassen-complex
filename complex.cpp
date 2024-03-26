#include <iostream>
#include <string>
#include "complex.h"
using namespace std;

Complex Complex::split(string cnum)
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

Complex Complex::operator-(Complex &subtractend)
{
    return Complex(this->r - subtractend.r, this->i - subtractend.i);
}

Complex Complex::operator*(Complex &factor)
{
    return Complex(this->r * factor.r - this->i * factor.i, this->i * factor.r + this->r * factor.i);
}

void Complex::print()
{
    cout << this->format() << endl;
}
