#include <algorithm>
#include <string>
#include "maze_creator.hpp"

using namespace std;

const maze_data *maze_create(const vector<string> &source) {
    auto *maze = new maze_data;
    int height;
    int width;
    if (source.empty())
        return nullptr;
    width = count_if(source[0].begin(), source[0].end(), [](char c) { return isdigit(c); });
    height = source.size();
    maze->height = height;
    maze->width = width;
    vector<point> field;
    int y = 0;
    int check_size;
    for (const auto &line : source) {
        int x = 0;
        check_size = count_if(line.begin(), line.end(), [](char c) { return isdigit(c); });
        if (check_size != width)
            return nullptr;
        for (auto elem: line) {
            int i = 0;
            int cur_state;
            if(isdigit(elem)) {
                cur_state = stoi(&elem);
            } else
                continue;
            point cur{};
            if(cur_state >= static_cast<int>(State::EMPTY) && cur_state <= static_cast<int>(State::EXIT)) {
                cur = point(x, y, static_cast<State>(cur_state));
            } else
                return nullptr;
            field.push_back(cur);
            x++;
        }
        y++;
    }
    maze->field = field;
    return maze;
}
