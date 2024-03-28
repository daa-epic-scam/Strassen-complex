#include "matrix.h"
#include <iostream>
#include <fstream>

int main(void)
{
    cout << endl;
    Matrix m1 = Matrix(3, 3);
    m1.set_data(0, 0, Complex(1, 2));
    m1.set_data(0, 1, Complex(3, 4));
    m1.set_data(0, 2, Complex(15, 16));
    m1.set_data(1, 0, Complex(7, 8));
    m1.set_data(1, 1, Complex(9, 10));
    m1.set_data(1, 2, Complex(17, 18));
    m1.set_data(2, 0, Complex(5, 6));
    m1.set_data(2, 1, Complex(11, 12));
    m1.set_data(2, 2, Complex(13, 14));
    cout << "Matrix 1:" << endl;
    m1.print();

    Matrix m2 = Matrix(3, 3);
    m2.set_data(0, 0, Complex(1, 2));
    m2.set_data(0, 1, Complex(3, 4));
    m2.set_data(0, 2, Complex(5, 6));
    m2.set_data(1, 0, Complex(7, 8));
    m2.set_data(1, 1, Complex(9, 10));
    m2.set_data(1, 2, Complex(11, 12));
    m2.set_data(2, 0, Complex(13, 14));
    m2.set_data(2, 1, Complex(15, 16));
    m2.set_data(2, 2, Complex(17, 18));
    cout << "Matrix 2:" << endl;
    m2.print();

    cout << "Iterative:" << endl;
    Matrix r = m1.iter_multiply(m2);
    r.print();

    m1.strassen(m2);
    return 0;
}
