#include "matrix.h"
#include <fstream>
#include <iostream>

int main()
{
    Matrix m = Matrix(2, 2);
    for (int i = 1; i < 5; i++) {
        m.set_data(i-1, Complex(i, i*i));
    }
    m.print();

    Matrix sum = m + m;
    sum.print();

    cout << "product: " << endl;

    Matrix product = m.iter_multiply(m);

    product.print();
}
