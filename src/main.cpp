//
#include <chrono>
#include "../include/complex.h"
#include "../include/matrix.h"
#include "../include/parse.h"
#include <fstream>
#include <iostream>
using namespace std;
using namespace std::chrono;

int main(void)
{
    std::string test_no = "testcase5.txt"; // change this to change the testcase number 
                                           // directory is in tests/testcases 
                                           // in case you would like to generate your own
                                           // testcases, use utility/matrix_gen.py (set params)
                                           // and add the matrices into your test file
    
    auto data = Parse::load("tests/testcases/"+test_no);
    auto matrices = Parse::init_n(data, "#"); // 2nd argument is delimter, important do not change

    cout << "Iterative multiplication" << endl; 
    matrices[0].iter_multiply(matrices[1]).print();
    
    cout << "Recursive multiplication" << endl; 
    matrices[0].recursive_multiply(matrices[1]).print();
    
    cout << "Strassen multiplication" << endl; 
    matrices[0].strassen(matrices[1]).print();
}
