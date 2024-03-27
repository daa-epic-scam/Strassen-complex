#include "matrix.h"
#include <fstream>
#include <iostream>
int main()
{
    Matrix m = Matrix(3, 3);
    for (int i = 0; i < 9; i++)
    {
        m.set_data(i, Complex(i, i * i));
    }
    cout << "printing matrix a" << endl;
    m.print();

    Matrix n = Matrix(3, 3);
    for (int i = 0; i < 9; i++)
    {
        n.set_data(i, Complex(i, i * i));
    }

    cout << "printing matrix b" << endl;
    n.print();

    cout << "product: " << endl;

    Matrix product = m.iter_multiply(n);

    product.print();
}
