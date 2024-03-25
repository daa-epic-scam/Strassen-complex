#include "matrix.h"

Matrix::Matrix(int rows_, int cols_)
{
    this->rows_ = rows_;
    this->cols_ = cols_;
    data_ = new Complex[rows_ * cols_];
}

int Matrix::rows() const
{
    return rows_;
}

int Matrix::cols() const
{
    return cols_;
}

// access elements in matrix
Complex &Matrix::at(int row_index, int col_index)
{
    if (row_index >= rows_ || col_index >= cols_)
    {
        throw std::out_of_range("Indices out of range");
    }
    return data_[row_index * cols_ + col_index];
}

// destructor
Matrix::~Matrix()
{
    delete[] data_;
}
