#include <iostream>
#include "complex.h"

template <class T>
class Matrix {
    int rows;
    int cols;
    T **matrix;

    public:
    Matrix(int rows, int cols, T values) {
        this->rows = rows;
        this->cols = cols;
        this->matrix = new T*[rows];

        for (int i = 0; i < rows; i++) {
            this->matrix[i] = new T[cols];
        }
    }
};
