#include "complex.h"

int main() {
    Complex c1 = Complex(1, 1);
    Complex c2 = Complex(2, 2);
    
    c1.print();
    c1.print();
    (c1 + c2).print();
    (c1 * c2).print();
}
