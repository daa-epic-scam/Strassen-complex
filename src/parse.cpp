#include "../include/parse.h"

std::vector<Complex> Parse::parse(std::string data)
{
    int start;
    int end = -1;
    std::vector<Complex> arr;
    int i = 0;
    do
    {
        start = end + 1;
        end = data.find(",", start);
        arr.push_back(Complex(data.substr(start, end - start)));
        i++;
    } while (end != -1);

    return arr;
}

std::vector<std::string> Parse::load(string path)
{
    std::ifstream file(path);       // Open the file
    std::vector<std::string> lines; // Vector to store the lines

    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {                          // Read lines from the file
            lines.push_back(line); // Add line to the vector
        }
        file.close(); // Close the file
    }
    else
    {
        std::cout << "Unable to open file" << std::endl;
    }

    return lines;
}

Matrix Parse::init(std::vector<std::string> data)
{
    int index = data[0].find(',');
    int rows = stoi(data[0].substr(0, index));

    std::string temp = data[0].substr(index + 1);

    int cols = stoi(temp.erase(temp.length()));

    Matrix m = Matrix(rows, cols);

    for (int i = 1; i < rows + 1; i++)
    {
        std::string line = data[i].erase(data[i].length());

        std::vector<Complex> vals = parse(data[i]);
        for (int j = 0; j < cols; j++)
        {
            m.set_data(i - 1, j, vals[j]);
        }
    }

    return m;
}

std::vector<Matrix> Parse::init_n(std::vector<std::string> data, std::string delimiter = "#")
{
    std::vector<Matrix> matrices;

    auto start = data.begin();
    auto end = data.end();

    while (start != end)
    {
        auto loc = std::find(start, end, delimiter);

        if (loc == end)
        {
            std::vector<std::string> matrix(start, end);
            matrices.push_back(init(matrix));
            break;
        }

        std::vector<std::string> matrix(start, loc);
        matrices.push_back(init(matrix));

        start = loc;
        if (start != end)
        {
            ++start;
        }
    }

    return matrices;
}

