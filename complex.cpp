#include <iostream>
#include "complex.h"

Complex Complex::split(std::string cnum)
{
    float real = 0; // PLACEHOLDER
    float im = 0;
    return Complex(real, im);
}

std::string Complex::format()
{
    return std::to_string(this->r) + " + " + std::to_string(this->i) + "i";
}

Complex::Complex(float r, float i)
{
    this->r = r;
    this->i = i;
}

Complex::Complex(std::string cnum)
{
    Complex c = split(cnum);
    this->r = c.r;
    this->i = c.i;
}

Complex Complex::operator+(Complex &factor)
{
    return Complex(this->r + factor.r, this->i + factor.i);
}

Complex Complex::operator*(Complex &factor)
{
    return Complex(this->r * factor.r - this->i * factor.i, this->i * factor.r + this->r * factor.i);
}

void Complex::print()
{
    std::cout << this->format() << std::endl;
}
