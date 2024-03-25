#include "matrix.h"
#include <fstream>
#include <iostream>

int main()
{
    Complex c1 = Complex(1, 1);
    Complex c2 = Complex(2, 2);
    Complex c3 = Complex("100+2000i");
    c1.print();
    c2.print();
    c3.print();
    (c1 + c2).print();
    (c1 * c2).print();

    string data;
    ifstream file;
    file.open("input.txt");
    file >> data;
    file.close();
    int start;
    int end = -1;
    Complex cnum;
    Complex *arr[4];
    int i = 0;
    do
    {
        start = end + 1;
        end = data.find(",", start);
        arr[i] = new Complex(data.substr(start, end - start));
        i++;
    } while (end != -1);

    // arr = new Complex[4]{c1, c3, (c1 + c2), (c1 * c2)};

    for (int i = 0; i < 4; i++)
    {
        arr[i]->print();
    }

    delete[] *arr;

    Matrix m = Matrix(2, 2);
    m.at(0, 0).print();
}
