#include "matrix.h"
#include <fstream>
#include <iostream>

int main()
{
    Matrix m = Matrix(2, 2);
    for (int i = 0; i < 4; i++) {
        m.set_data(i, Complex(i, i*i));
    }
    m.print();

    Matrix sum = m + m;
    sum.print();

    cout << "hello there";
}
