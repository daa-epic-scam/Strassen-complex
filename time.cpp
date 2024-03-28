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
    auto start = high_resolution_clock::now();
    function();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
}