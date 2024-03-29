//

#include "complex.h"
#include "matrix.h"
#include "parse.h"
#include <fstream>
#include <iostream>
int main()
{
    cout << "loading file sample into matrix: " << endl;
    std::vector<std::string> lines = Parse::load("tests/test.txt");

    Matrix m = Parse::init(lines);
    m.print();
}
