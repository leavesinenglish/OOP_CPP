#ifndef WAVE_ALG_MAZE_CREATOR_HPP
#define WAVE_ALG_MAZE_CREATOR_HPP
#include <vector>
#include <string>

enum class State {
    EMPTY = 0,
    WALL = 1,
    HERO = 2,
    EXIT = 3
};

struct point final{
    int x;
    int y;
    State state;
    point() = default;
    inline point(int x, int y, State state = State::EMPTY) : x(x), y(y), state(state) {};
};

inline bool operator==(point left, point right) {
    return ((left.x == right.x) & (left.y == right.y) & (left.state == right.state));
}


struct maze_data final{
    std::vector<point> field;
    int height;
    int width;
};

const maze_data *maze_create(const std::vector<std::string>& source);

#endif //WAVE_ALG_MAZE_CREATOR_HPP