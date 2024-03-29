#ifndef PARSE_H
#define PARSE_H


#include <iostream>
#include <fstream>
#include <vector>
#include "complex.h"
#include "matrix.h"
#include <valarray>

using namespace std;

class Parse {
private:
    static std::vector<Complex> parse(std::string);

public:
    static std::vector<std::string> load(string);

    static Matrix init(std::vector<std::string>);

    static std::vector<Matrix> init_n(std::vector<std::string>, std::string);
};

#endif // !PARSE_H
