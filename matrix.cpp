#include <iostream>

class Complex
{
public:
    double real, imag;

    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    Complex operator+(const Complex &other) const
    {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator-(const Complex &other) const
    {
        return Complex(real - other.real, imag - other.imag);
    }

    Complex operator*(const Complex &other) const
    {
        return Complex(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
    }
};

class Matrix
{
public:
    // constructor for number of rows and columns in matrix
    Matrix(size_t rows = 0, size_t cols = 0) : rows_(rows), cols_(cols), data_(new Complex[rows * cols]) {}

    size_t rows() const
    {
        return rows_;
    }

    size_t cols() const
    {
        return cols_;
    }

    // access elements in matrix
    Complex &at(size_t row_index, size_t col_index)
    {
        if (row_index >= rows_ || col_index >= cols_)
        {
            throw std::out_of_range("Indices out of range");
        }
        return data_[row_index * cols_ + col_index];
    }

    // destructor
    ~Matrix()
    {
        delete[] data_;
    }

private:
    size_t rows_;
    size_t cols_;
    Complex *data_;
};
