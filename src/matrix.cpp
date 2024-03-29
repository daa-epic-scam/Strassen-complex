#include "matrix.h"

Matrix::

    Matrix::Matrix(int rows_, int cols_) : rows_(rows_), cols_(cols_)
{
    data_ = new Complex[rows_ * cols_];
}

Matrix::Matrix(Matrix const &other) : rows_(other.rows_), cols_(other.cols_)
{
    data_ = new Complex[rows_ * cols_];
    for (int i = 0; i < rows_ * cols_; ++i)
    {
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

Complex Matrix::data(int ind)
{
    return this->data_[ind];
}

void Matrix::set_data(int ind, Complex cnum)
{
    this->data_[ind] = cnum;
}

void Matrix::set_data(int row, int col, Complex cnum)
{

    if (row >= rows_ || col >= cols_)
    {
        throw std::out_of_range("Indices out of range");
    }
    this->data_[row * cols_ + col] = cnum;
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

Matrix Matrix::operator+(Matrix addend)
{
    if (this->rows_ == 0)
    {
        return addend;
    }
    if (addend.rows_ == 0)
    {
        return *this;
    }
    if (this->rows_ != addend.rows() || this->cols_ != addend.cols())
    {
        throw std::invalid_argument("Incompatible matrix dimensions");
    }

    Matrix sum = Matrix(rows_, cols_);

    for (int i = 0; i < cols_ * rows_; i++)
    {
        sum.set_data(i, this->data(i) + addend.data(i));
    }

    return sum;
}

Matrix Matrix::operator-(Matrix subtrahend)
{
    if (this->rows_ == 0)
    {
        return subtrahend;
    }
    if (subtrahend.rows_ == 0)
    {
        return *this;
    }
    if (this->rows_ != subtrahend.rows() || this->cols_ != subtrahend.cols())
    {
        throw std::invalid_argument("Incompatible matrix dimensions");
    }

    Matrix diff = Matrix(rows_, cols_);

    for (int i = 0; i < cols_ * rows_; i++)
    {
        diff.set_data(i, this->data(i) - subtrahend.data(i));
    }

    return diff;
}

Matrix Matrix::iter_multiply(Matrix factor)
{
    if (this->cols_ != factor.rows())
    {
        throw std::invalid_argument("Incompatible matrix dimensions");
    }

    Matrix product = Matrix(this->rows_, factor.cols());

    for (int i = 0; i < this->rows_; i++)
    {
        for (int j = 0; j < factor.cols(); j++)
        {
            Complex res = Complex(0, 0);
            for (int k = 0; k < this->cols_; k++)
            {
                res = res + this->at(i, k) * factor.at(k, j);
            }
            product.set_data(i * factor.cols() + j, res);
        }
    }

    return product;
}

Matrix Matrix::cut_matrix(int startrow, int startcol, int endrow, int endcol)
{
    if (endrow - startrow == 0 || endcol - startcol == 0)
    {
        return Matrix(0, 0);
    }
    Matrix newmat = Matrix(endrow - startrow, endcol - startcol);
    for (int i = startrow; i < endrow; i++)
    {
        for (int j = startcol; j < endcol; j++)
        {
            newmat.set_data(i - startrow, j - startcol, this->at(i, j));
        }
    }
    return newmat;
}

void Matrix::fill_by_matrix(int startrow, int startcol, Matrix smallmat)
{
    for (int i = startrow; i < startrow + smallmat.rows(); i++)
    {
        for (int j = startcol; j < startcol + smallmat.cols(); j++)
        {
            this->set_data(i, j, smallmat.at(i - startrow, j - startcol));
        }
    }
}

void Matrix::print()
{
    cout << "--------------------------------------" << endl;
    for (int i = 0; i < rows_; i++)
    {
        for (int j = 0; j < cols_; j++)
        {
            cout << this->at(i, j).format() + " ";
        }
        cout << endl;
    }
    cout << "--------------------------------------" << endl;
}

// destructor
Matrix::~Matrix()
{
    delete[] data_;
}

Matrix Matrix::dnc_multiply(Matrix a, Matrix b)
{
    if ((a.rows() == 0 && a.cols() == 0) && (b.rows() == 0 && b.cols() == 0))
    {
        return Matrix(0, 0);
    }
    if (a.cols() != b.rows())
    {
        return Matrix(0, 0);
        // throw std::invalid_argument("Incompatible matrix dimensions");
    }
    if ((a.rows() == 1 && a.cols() == 1) && (b.rows() == 1 && b.cols() == 1))
    {
        Matrix c = Matrix(1, 1);
        c.set_data(0, 0, a.at(0, 0) * b.at(0, 0));
        return c;
    }
    int splitrows = a.rows() - (a.rows() / 2);
    int splitcols = a.cols() - (a.cols() / 2);

    // splitting of matrices into 4 quadrants
    Matrix mat1a = a.cut_matrix(0, 0, splitrows, splitcols);
    Matrix mat2a = a.cut_matrix(0, splitcols, splitrows, a.cols());
    Matrix mat3a = a.cut_matrix(splitrows, 0, a.rows(), splitcols);
    Matrix mat4a = a.cut_matrix(splitrows, splitcols, a.rows(), a.cols());

    Matrix mat1b = b.cut_matrix(0, 0, splitrows, splitcols);
    Matrix mat2b = b.cut_matrix(0, splitcols, splitrows, b.cols());
    Matrix mat3b = b.cut_matrix(splitrows, 0, b.rows(), splitcols);
    Matrix mat4b = b.cut_matrix(splitrows, splitcols, b.rows(), b.cols());

    // recursive calls for multiplying matrices, 8 multiplication and 4 additions
    Matrix mat1 = dnc_multiply(mat1a, mat1b) + dnc_multiply(mat2a, mat3b);
    Matrix mat2 = dnc_multiply(mat1a, mat2b) + dnc_multiply(mat2a, mat4b);
    Matrix mat3 = dnc_multiply(mat3a, mat1b) + dnc_multiply(mat4a, mat3b);
    Matrix mat4 = dnc_multiply(mat3a, mat2b) + dnc_multiply(mat4a, mat4b);

    int rows = mat1.rows() + mat3.rows();
    int cols = mat1.cols() + mat2.cols();
    // making the new matrix
    Matrix merged = Matrix(rows, cols);
    // merging
    merged.fill_by_matrix(0, 0, mat1);
    merged.fill_by_matrix(0, mat1.cols(), mat2);
    merged.fill_by_matrix(mat1.rows(), 0, mat3);
    merged.fill_by_matrix(mat1.rows(), mat1.cols(), mat4);
    return merged;
}

int max_num(int m1_rows, int m1_cols, int m2_rows, int m2_cols)
{
    if (m1_cols != m2_rows)
    {
        throw std::invalid_argument("Invalid matrix dimensions");
    }
    if (m1_rows >= m1_cols && m1_rows >= m2_rows && m1_rows >= m2_cols)
    {
        return m1_rows;
    }
    else if (m1_cols >= m1_rows && m1_cols >= m2_rows && m1_cols >= m2_cols)
    {
        return m1_cols;
    }
    else if (m2_rows >= m1_rows && m2_rows >= m1_cols && m2_rows >= m2_cols)
    {
        return m2_rows;
    }
    else
    {
        return m2_cols;
    }
}

Matrix Matrix::pad(Matrix m1, int new_rows)
{
    if (m1.rows() == 0)
    {
        throw std::invalid_argument("Matrix dimensions can not be zero");
    }
    new_rows = pow(2, ceil(log2(new_rows)));
    Matrix new_m1 = Matrix(new_rows, new_rows);
    for (int i = 0; i < new_rows; i++)
    {
        for (int j = 0; j < new_rows; j++)
        {
            new_m1.set_data(i, j, Complex(0, 0));
        }
    }
    new_m1.fill_by_matrix(0, 0, m1);
    return new_m1;
}

Matrix Matrix::strassen_multiply(Matrix A, Matrix B)
{
    // base case
    if ((A.rows() == 1 && A.cols() == 1) && (B.rows() == 1 && B.cols() == 1))
    {
        Matrix C = Matrix(1, 1);
        C.set_data(0, 0, A.at(0, 0) * B.at(0, 0));
        return C;
    }

    int splitrows = A.rows() - floor((A.rows() / 2));
    int splitcols = A.cols() - floor((A.cols() / 2));

    Matrix A11 = A.cut_matrix(0, 0, splitrows, splitcols);
    Matrix A12 = A.cut_matrix(0, splitcols, splitrows, A.cols());
    Matrix A21 = A.cut_matrix(splitrows, 0, A.rows(), splitcols);
    Matrix A22 = A.cut_matrix(splitrows, splitcols, A.rows(), A.cols());

    Matrix B11 = B.cut_matrix(0, 0, splitrows, splitcols);
    Matrix B12 = B.cut_matrix(0, splitcols, splitrows, B.cols());
    Matrix B21 = B.cut_matrix(splitrows, 0, B.rows(), splitcols);
    Matrix B22 = B.cut_matrix(splitrows, splitcols, B.rows(), B.cols());

    Matrix S1 = strassen_multiply(A11 + A22, B11 + B22);
    Matrix S2 = strassen_multiply(A21 + A22, B11);
    Matrix S3 = strassen_multiply(A11, B12 - B22);
    Matrix S4 = strassen_multiply(A22, B21 - B11);
    Matrix S5 = strassen_multiply(A11 + A12, B22);
    Matrix S6 = strassen_multiply(A21 - A11, B11 + B12);
    Matrix S7 = strassen_multiply(A12 - A22, B21 + B22);

    Matrix C11 = S1 + S4 - S5 + S7;
    Matrix C12 = S3 + S5;
    Matrix C21 = S2 + S4;
    Matrix C22 = S1 + S3 + S6 - S2;

    int rows = C11.rows() + C21.rows();
    int cols = C11.cols() + C12.cols();

    Matrix C = Matrix(rows, cols);
    C.fill_by_matrix(0, 0, C11);
    C.fill_by_matrix(0, C12.cols(), C12);
    C.fill_by_matrix(C11.rows(), 0, C21);
    C.fill_by_matrix(C11.rows(), C12.cols(), C22);
    return C;
}

void Matrix::strassen(Matrix m2)
{
    Matrix m1 = *this;
    int dim = max_num(m1.rows(), m1.cols(), m2.rows(), m2.cols());
    Matrix new_m1 = Matrix(dim, dim);
    Matrix new_m2 = Matrix(dim, dim);
    Matrix p = strassen_multiply(new_m1.pad(m1, dim), new_m2.pad(m2, dim));
    Matrix new_p = p.cut_matrix(0, 0, m1.rows(), m2.cols());
    cout << "Strassen: " << endl;
    new_p.print();
}

void Matrix::recursive_multiply(Matrix m2)
{
    Matrix p = dnc_multiply(*this, m2);
    cout << "Conventional Recursive: " << endl;
    p.print();
}