#include "matrix.h"
#include <iostream>
#include <fstream>
#include <cmath>

Matrix multiply_dnc(Matrix a, Matrix b)
{
    if (a.cols() != b.rows())
    {
        throw std::invalid_argument("Incompatible matrix dimensions");
    }

    if ((a.rows() == 1 && a.cols() == 1) && (b.rows() == 1 && b.cols() == 1))
    {
        Matrix c = Matrix(1, 1);
        c.set_data(0, 0, a.at(0, 0) * b.at(0, 0));
        return c;
    }

    int splitrows = a.rows() - (a.rows() / 2);
    int splitcols = a.cols() - (a.cols() / 2);

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
    merged.fill_by_matrix(0, mat2.cols(), mat2);
    merged.fill_by_matrix(mat1.rows(), 0, mat3);
    merged.fill_by_matrix(mat1.rows(), mat2.cols(), mat4);

    return merged;
}



Matrix strassen_multiply(Matrix A, Matrix B){

    if (A.cols() != B.rows()) // check if the matrices are compatible for multiplication
    {
        throw std::invalid_argument("Incompatible matrix dimensions");
    }

    if ((A.rows() == 1 && A.cols() == 1) && (B.rows() == 1 && B.cols() == 1))
    {
        Matrix C = Matrix(1, 1);
        C.set_data(0, 0, A.at(0, 0) * B.at(0, 0));
        return C;
    }

    int splitrows = A.rows() - (A.rows() / 2);
    int splitcols = A.cols() - (A.cols() / 2);

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
    Matrix S3 = strassen_multiply(A11,B12 - B22);
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

int main(void){
    Matrix m1 = Matrix(2, 2);
    m1.set_data(0, 0, Complex(1, 2));
    m1.set_data(0, 1, Complex(3, 4));
    m1.set_data(1, 0, Complex(5, 6));
    m1.set_data(1, 1, Complex(7, 8));
    m1.print();

    Matrix m2 = Matrix(2, 2);
    m2.set_data(0, 0, Complex(1, 2));
    m2.set_data(0, 1, Complex(3, 4));
    m2.set_data(1, 0, Complex(5, 6));
    m2.set_data(1, 1, Complex(7, 8));

    Matrix p = strassen_multiply(m1, m2);
    cout << "Strassen" << endl;
    p.print();
    Matrix q = multiply_dnc(m1, m2);
    cout << "Divide and Conquer" << endl;
    q.print();
    cout << "Iterative" << endl;
    Matrix r = m1.iter_multiply(m2);
    r.print(); 
    return 0;
}