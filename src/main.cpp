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
    cout << "loading file sample into matrix: " << endl;
    std::vector<std::string> lines = Parse::load("tests/test.txt");

    Matrix m = Parse::init(lines);
    m.print();

    auto start = high_resolution_clock::now();
    m.iter_multiply(m);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by Conventional Recursive: " << duration.count() << " microseconds" << endl;

    auto start = high_resolution_clock::now();
    m.recursive_multiply(m);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by Conventional Recursive: " << duration.count() << " microseconds" << endl;

    auto start = high_resolution_clock::now();
    m.strassen(m);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by Conventional Recursive: " << duration.count() << " microseconds" << endl;
}
