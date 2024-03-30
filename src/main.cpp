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
    // cout << "loading file sample into matrix: " << endl;
    std::vector<std::string> lines = Parse::load("tests/test9.txt");

    Matrix m = Parse::init(lines);
    // m.print();
    cout << "Loaded the Matrix from the file of size: " << m.rows() << "x" << m.cols() << endl;
    auto start = high_resolution_clock::now();
    m.iter_multiply(m);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by Iterative Multiplication: " << duration.count() << " microseconds" << endl;

    start = high_resolution_clock::now();
    m.recursive_multiply(m);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by Conventional Recursive Multiplication: " << duration.count() << " microseconds" << endl;

    start = high_resolution_clock::now();
    m.strassen(m);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by Strassen's Multiplication: " << duration.count() << " microseconds" << endl;
}
