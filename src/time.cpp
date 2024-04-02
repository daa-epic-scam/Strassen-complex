#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;

void function()
{
    // Code to measure time
    cout << "function is running \n";
    return;
}

int main(void)
{
    // cout << "loading file sample into matrix: " << endl;
    std::vector<std::string> lines = Parse::load("tests/output.txt");
    // std::vector<Matrix> matrices;
    auto matrices = Parse::init_n(lines, "#");
    auto start = high_resolution_clock::now();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::vector<double> iterative_times;
    std::vector<double> recursive_times;
    std::vector<double> strassen_times;
    for (int i = 0; i < matrices.size(); i++)
    {
        // matrices[i].print();
        // cout << "Loaded the Matrix from the file of size: " << matrices[i].rows() << "x" << matrices[i].cols() << endl;
        start = high_resolution_clock::now();
        matrices[i].iter_multiply(matrices[i]);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        // cout << "Time taken by Iterative Multiplication: " << duration.count() << " microseconds" << endl;
        iterative_times.push_back(duration.count());

        start = high_resolution_clock::now();
        matrices[i].recursive_multiply(matrices[i]);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        // cout << "Time taken by Conventional Recursive Multiplication: " << duration.count() << " microseconds" << endl;
        recursive_times.push_back(duration.count());

        start = high_resolution_clock::now();
        matrices[i].strassen(matrices[i]);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        // cout << "Time taken by Strassen's Multiplication: " << duration.count() << " microseconds" << endl;
        strassen_times.push_back(duration.count());
    }
    cout << "iterative,recursive,strassen" << endl;
    for (int i = 0; i < iterative_times.size(); i++) {
        cout << iterative_times[i] << "," << recursive_times[i] << "," << strassen_times[i] << endl;
    }
}
