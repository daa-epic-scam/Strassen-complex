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

    auto m = Parse::init_n(lines, "#");
    for (auto i: m) {
        i.print();
    }
}
