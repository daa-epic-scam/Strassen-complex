#include "matrix.h"

Matrix::Matrix(int rows_, int cols_) : rows_(rows_), cols_(cols_)
{
    data_ = new Complex[rows_ * cols_];
}

Matrix::Matrix(Matrix const& other) : rows_(other.rows_), cols_(other.cols_) {
    data_ = new Complex[rows_ * cols_];
    for (int i = 0; i < rows_ * cols_; ++i) {
        data_[i] = other.data_[i];
    }
}

int Matrix::rows() const
{
    return rows_;
}

int Matrix::cols() const
{
    return cols_;
}

Complex Matrix::data(int ind) {
   return this->data_[ind]; 
}

void Matrix::set_data(int ind, Complex cnum) {
    this->data_[ind] = cnum;
}

// access elements in matrix
Complex Matrix::at(int row_index, int col_index)
{
    if (row_index >= rows_ || col_index >= cols_)
    {
        throw std::out_of_range("Indices out of range");
    }
    return data_[row_index * cols_ + col_index];
}

Matrix Matrix::operator+(Matrix addend) {
    if (this->rows_ != addend.rows() || this->cols_ != addend.cols()){
        throw std::invalid_argument("Incompatible matrix dimensions");
    }

    Matrix sum = Matrix(rows_, cols_);

    for (int i = 0; i < cols_ * rows_; i++) {
        sum.set_data(i, this->data(i) + addend.data(i));
    }

    return sum;
}

Matrix Matrix::operator-(Matrix subtrahend) {
    if (this->rows_ != subtrahend.rows() || this->cols_ != subtrahend.cols()){
        throw std::invalid_argument("Incompatible matrix dimensions");
    }

    Matrix diff = Matrix(rows_, cols_);

    for (int i = 0; i < cols_ * rows_; i++) {
        diff.set_data(i, this->data(i) - subtrahend.data(i));
    }

    return diff;
}

Matrix Matrix::iter_multiply(Matrix factor) {
    if (this->cols_ != factor.rows()) {
        throw std::invalid_argument("Incompatible matrix dimensions");
    }

    Matrix product = Matrix(this->rows_, factor.cols());
    
    for (int i = 0; i < this->rows_; i++) {
        for (int j = 0; j < this->cols_; j++) {
            Complex res = Complex(0, 0);
            for (int k = 0; k < this->rows_; k++) {
                res = res + this->at(i, k) * factor.at(k, j);
            }
            product.set_data(i*factor.cols()+j, res);
        }
    }

    return product;
}

void Matrix::print() {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            cout << this->at(i, j).format() + " ";
        }
        cout << endl;
    }
}


// destructor
Matrix::~Matrix()
{
    delete[] data_;
}
