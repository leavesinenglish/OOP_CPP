#ifndef WAVE_ALG_WAVE_ALG_HPP
#define WAVE_ALG_WAVE_ALG_HPP

#include <vector>
#include <string>
#include "maze_creator.hpp"

std::vector<int> wave_motion(const maze_data *maze_data);
std::vector<point> find_path(std::vector<int> wave_map, const maze_data *maze);
#endif //WAVE_ALG_WAVE_ALG_HPP