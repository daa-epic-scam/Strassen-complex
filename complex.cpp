#include <iostream>
#include "complex.h"

Complex Complex::split(std::string cnum) {
    float real = 0; // PLACEHOLDER 
    float im = 0;
    return Complex(real, im);
}

std::string Complex::format() {
    return std::to_string(this->r) + " + " + std::to_string(this->i) + "i";
}

Complex::Complex(float r, float i) {
    this->r = r;
    this->i = i;
}

Complex::Complex(std::string cnum) {
    Complex c = split(cnum);
    this->r = c.r;
    this->i = c.i;
}

Complex Complex::operator+(Complex& addend) {
    return Complex(this->r + addend.r, this->i + addend.i);
}

Complex Complex::operator*(Complex& addend) {
    return Complex(this->r * addend.r - this->i * addend.i, this->i * addend.r + this->r * addend.i);
}

void Complex::print() {
    std::cout << this->format() << std::endl;
}
