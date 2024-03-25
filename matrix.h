#ifndef COMPLEX_H


#include <iostream>
#include "complex.h"

class Matrix
{
private:
    int rows_;
    int cols_;
    Complex *data_;
    
public:
    // constructor for number of rows and columns in matrix
    Matrix(int, int);

    int rows() const;

    int cols() const;

    // access elements in matrix
    Complex& at(int, int);

    // destructor
    ~Matrix();
};

#endif // !COMPLEX_H

