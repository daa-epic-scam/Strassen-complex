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

    Matrix(Matrix const&);

    int rows() const;

    int cols() const;

    Complex data(int);
    
    void set_data(int, Complex);
    
    // access elements in matrix
    Complex at(int, int);

    Matrix operator+(Matrix);
    
    Matrix operator-(Matrix);

    // Matrix operator*(Matrix);
    
    void print();

    // destructor
    ~Matrix();
};

#endif // !COMPLEX_H

