#include <string>
#include "work_with_file.hpp"
using namespace std;

vector<string> parser(istream &input) {
    vector<string> maze;
    string line;
    while (getline(input, line))
        maze.push_back(line);
    return maze;
}