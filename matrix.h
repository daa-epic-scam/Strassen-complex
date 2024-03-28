#ifndef COMPLEX_H

#include <cmath>
#include <iostream>
#include "complex.h"

class Matrix
{
private:
    int rows_;
    int cols_;
    Complex *data_;
    
    bool isPowerOf2(int);

    Matrix padding_matrix(Matrix);

    Matrix strassen_multiply(Matrix, Matrix);


public:
    // constructor for number of rows and columns in matrix
    Matrix(int, int);

    Matrix(Matrix const &);

    int rows() const;

    int cols() const;

    Complex data(int);

    void set_data(int, Complex);

    void set_data(int, int, Complex);
    // access elements in matrix
    Complex at(int, int);

    Matrix operator+(Matrix);

    Matrix operator-(Matrix);

    Matrix cut_matrix(int startrow, int startcol, int endrow, int endcol);

    void fill_by_matrix(int startrow, int startcol, Matrix smallmat);

    Matrix iter_multiply(Matrix);
    
    void strassen(Matrix);

    void print();

    // destructor
    ~Matrix();
};

#endif // !COMPLEX_H
