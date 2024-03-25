// #include "complex.h"
#include "matrix.h"

int main() {
    Complex c1 = Complex(1, 1);
    Complex c2 = Complex(2, 2);
    
    c1.print();
    c2.print();
    (c1 + c2).print();
    (c1 * c2).print();
    
    Complex *arr;

    arr = new Complex[4] { c1, c2, (c1+c2), (c1*c2) };


    for (int i = 0; i < 4; i++) {
        arr[i].print();
    }

    delete []arr;

    Matrix m = Matrix(2, 2);
    m.at(0, 0).print();
}
