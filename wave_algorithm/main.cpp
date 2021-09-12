#include <iostream>
#include <fstream>
#include <vector>
#include "work_with_file.hpp"
#include "maze_creator.hpp"
#include "wave_alg.hpp"
#include "output_wave_alg_solution.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    std::ifstream finp(argv[1]);
    std::istream &inp = finp;
    const maze_data *test = maze_create(parser(inp));
    if (test == nullptr) {
        std::cout << "Failed to create maze." << std::endl;
        return 0;
    }
    vector<int> wave = wave_motion(test);
    if (wave == vector<int>(0)){
        std::cout << "Wave propagation is not possible. Something wrong with your maze format: amount of heroes or exits." << std::endl;
        return 0;
    }
    vector <point> solution = find_path(wave_motion(test), test);
    if (solution == vector<point> (0)){
        std::cout << "No path to exit in the maze." << std::endl;
        return 0;
    }
    output_wave_alg_solution(test, solution);
    delete test;
    return 0;
}