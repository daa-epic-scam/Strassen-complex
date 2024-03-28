#include "matrix.h"
#include <iostream>
#include <fstream>
#include <cmath>

bool isPowerOf2(int n)
{
    if (n == 0)
    {
        return 0;
    }
    return (ceil(log2(n)) == floor(log2(n)));
}

Matrix padding_matrix(Matrix m1)
{
    int new_rows = pow(2, ceil(log2(m1.rows())));
    int new_cols = pow(2, ceil(log2(m1.cols())));
    Matrix new_m1 = Matrix(new_rows, new_cols);
    for (int i = new_rows - m1.rows(); i < new_rows; i++)
    {
        for (int j = new_cols - m1.cols(); j < new_cols; j++)
        {
            new_m1.set_data(i, j, Complex(0, 0));
        }
    }
    new_m1.fill_by_matrix(0, 0, m1);
    return new_m1;
}

Matrix multiply_dnc(Matrix a, Matrix b)
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
    Matrix mat1 = multiply_dnc(mat1a, mat1b) + multiply_dnc(mat2a, mat3b);
    Matrix mat2 = multiply_dnc(mat1a, mat2b) + multiply_dnc(mat2a, mat4b);
    Matrix mat3 = multiply_dnc(mat3a, mat1b) + multiply_dnc(mat4a, mat3b);
    Matrix mat4 = multiply_dnc(mat3a, mat2b) + multiply_dnc(mat4a, mat4b);

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

Matrix strassen_multiply(Matrix A, Matrix B)
{

    if ((A.cols() != A.rows()) && (B.cols() != B.rows()))
    {
        throw std::invalid_argument("Strassen: Matrix is not square");
    }

    if (A.cols() != B.rows()) // check if the matrices are compatible for multiplication
    {
        throw std::invalid_argument("Strassen: Incompatible matrix dimensions");
    }

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
    C.fill_by_matrix(0, C11.cols(), C12);
    C.fill_by_matrix(C11.rows(), 0, C21);
    C.fill_by_matrix(C11.rows(), C11.cols(), C22);

    return C;
}

int main(void)
{
    Matrix m1 = Matrix(3, 3);
    m1.set_data(0, 0, Complex(1, 2));
    m1.set_data(0, 1, Complex(3, 4));
    m1.set_data(0, 2, Complex(15, 16));
    m1.set_data(1, 0, Complex(7, 8));
    m1.set_data(1, 1, Complex(9, 10));
    m1.set_data(1, 2, Complex(17, 18));
    m1.set_data(2, 0, Complex(5, 6));
    m1.set_data(2, 1, Complex(11, 12));
    m1.set_data(2, 2, Complex(13, 14));
    m1.print();

    Matrix m2 = Matrix(3, 3);
    m2.set_data(0, 0, Complex(1, 2));
    m2.set_data(0, 1, Complex(3, 4));
    m2.set_data(0, 2, Complex(5, 6));
    m2.set_data(1, 0, Complex(7, 8));
    m2.set_data(1, 1, Complex(9, 10));
    m2.set_data(1, 2, Complex(11, 12));
    m2.set_data(2, 0, Complex(13, 14));
    m2.set_data(2, 1, Complex(15, 16));
    m2.set_data(2, 2, Complex(17, 18));
    m2.print();

    cout << "Iterative" << endl;
    Matrix r = m1.iter_multiply(m2);
    r.print();

    cout << "Recursive" << endl;
    Matrix s = multiply_dnc(m1, m2);
    s.print();

    if (!isPowerOf2(m1.rows()))
    {
        Matrix new_m1 = padding_matrix(m1);
        Matrix new_m2 = padding_matrix(m2);
        Matrix p = strassen_multiply(new_m1, new_m2);
        Matrix new_p = p.cut_matrix(0, 0, m1.rows(), m1.cols());
        cout << "Strassen" << endl;
        new_p.print();
    }
    else
    {
        Matrix p = strassen_multiply(m1, m2);
        cout << "Strassen" << endl;
        p.print();
    }

    return 0;
}