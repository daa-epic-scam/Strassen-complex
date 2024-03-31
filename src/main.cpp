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
    std::vector<std::string> lines = Parse::load("tests/test.txt");
    // std::vector<Matrix> matrices;
    auto matrices = Parse::init_n(lines, "#");
    cout << matrices.size() << endl;
    for (auto i : matrices)
    {
        i.print();
    }
    // auto start = high_resolution_clock::now();
    // auto stop = high_resolution_clock::now();
    // auto duration = duration_cast<microseconds>(stop - start);
    // std::vector<double> times;
    // std::vector<double> times1;
    // std::vector<double> times2;
    // for (int i = 0; i < matrices.size(); i++)
    // {
    //     // matrices[i].print();
    //     cout << "Loaded the Matrix from the file of size: " << matrices[i].rows() << "x" << matrices[i].cols() << endl;
    //     start = high_resolution_clock::now();
    //     matrices[i].iter_multiply(matrices[i]);
    //     stop = high_resolution_clock::now();
    //     duration = duration_cast<microseconds>(stop - start);
    //     cout << "Time taken by Iterative Multiplication: " << duration.count() << " microseconds" << endl;
    //     times.push_back(duration.count());

    //     start = high_resolution_clock::now();
    //     matrices[i].recursive_multiply(matrices[i]);
    //     stop = high_resolution_clock::now();
    //     duration = duration_cast<microseconds>(stop - start);
    //     cout << "Time taken by Conventional Recursive Multiplication: " << duration.count() << " microseconds" << endl;
    //     times1.push_back(duration.count());

    //     start = high_resolution_clock::now();
    //     matrices[i].strassen(matrices[i]);
    //     stop = high_resolution_clock::now();
    //     duration = duration_cast<microseconds>(stop - start);
    //     cout << "Time taken by Strassen's Multiplication: " << duration.count() << " microseconds" << endl;
    //     times2.push_back(duration.count());
    // }
}
