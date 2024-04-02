//
#include <chrono>
#include "complex.h"
#include "matrix.h"
#include "parse.h"
#include <fstream>
#include <iostream>
using namespace std;
using namespace std::chrono;

int main(void)
{
    std::vector<std::string> lines = Parse::load("tests/test1.txt");
    std::vector<std::string> lines2 = Parse::load("tests/test12.txt");
    Matrix m1 = Parse::init(lines);
    Matrix m2 = Parse::init(lines2);

    auto start = high_resolution_clock::now();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Loaded the Matrix 1 from the file of size: " << m1.rows() << "x" << m1.cols() << endl;
    m1.print();

    cout << "Loaded the Matrix 2 from the file of size: " << m2.rows() << "x" << m2.cols() << endl;
    m2.print();
    start = high_resolution_clock::now();
    Matrix mout1 = m1.iter_multiply(m2);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by Iterative Multiplication: " << duration.count() << " microseconds" << endl;

    start = high_resolution_clock::now();
    m1.recursive_multiply(m2);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by Conventional Recursive Multiplication: " << duration.count() << " microseconds" << endl;

    start = high_resolution_clock::now();
    m1.strassen(m2);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by Strassen's Multiplication: " << duration.count() << " microseconds" << endl;
}
