#include "matrix.h"
#include <fstream>
#include <iostream>

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
    // splitting of matrices into 4 quadrants
    cout << "cutting this matrix" << endl;
    a.print();
    cout << splitrows << "            " << splitcols << endl;
    Matrix mat1a = a.cut_matrix(0, 0, splitrows, splitcols);
    mat1a.print();
    Matrix mat2a = a.cut_matrix(0, splitcols, splitrows, a.cols());
    mat2a.print();
    Matrix mat3a = a.cut_matrix(splitrows, 0, a.rows(), splitcols);
    mat3a.print();
    Matrix mat4a = a.cut_matrix(splitrows, splitcols, a.rows(), a.cols());
    mat4a.print();

    Matrix mat1b = b.cut_matrix(0, 0, splitrows, splitcols);
    Matrix mat2b = b.cut_matrix(0, splitcols, splitrows, b.cols());
    Matrix mat3b = b.cut_matrix(splitrows, 0, b.rows(), splitcols);
    Matrix mat4b = b.cut_matrix(splitrows, splitcols, b.rows(), b.cols());

    // recursive calls for multiplying matrices, 8 multiplication and 4 additions
    Matrix mat1 = multiply_dnc(mat1a, mat1b) + multiply_dnc(mat2a, mat3b);
    Matrix mat2 = multiply_dnc(mat1a, mat2b) + multiply_dnc(mat2a, mat4b);
    Matrix mat3 = multiply_dnc(mat3a, mat1b) + multiply_dnc(mat4a, mat3b);
    Matrix mat4 = multiply_dnc(mat3a, mat3b) + multiply_dnc(mat4a, mat4b);

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

int main()
{
    Matrix m = Matrix(3, 3);
    for (int i = 0; i < 9; i++)
    {
        m.set_data(i, Complex(i, i + 2 * i + 3));
    }
    cout << "printing matrix a" << endl;
    m.print();

    Matrix n = Matrix(3, 3);
    for (int i = 1; i < 4; i++)
    {
        n.set_data(i - 1, Complex(i, i * i));
    }
    n.print();

    cout << "printing matrix b" << endl;
    n.print();

    Matrix epic = multiply_dnc(m, n);
    cout << "printing multiplication of a and b" << endl;
    epic.print();

    cout << "product: " << endl;

    Matrix product = m.iter_multiply(n);

    product.print();
}
