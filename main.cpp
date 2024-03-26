#include "matrix.h"
#include <fstream>
#include <iostream>

int main()
{
    Matrix m = Matrix(2, 3);
    for (int i = 1; i < 6; i++) {
        m.set_data(i-1, Complex(i, i*i));
    }
    m.print();

    Matrix n = Matrix(3, 2);
    for (int i = 1; i < 6; i++) {
        n.set_data(i-1, Complex(i, i*i));
    }
    n.print();
    
    // Matrix sum = m + m;
    // sum.print();

    cout << "product: " << endl;

    Matrix product = m.iter_multiply(n);

    product.print();
}
