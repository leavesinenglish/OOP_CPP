#include "wave_alg.hpp"
#include <queue>
#include <map>
#include <cassert>

using namespace std;
namespace {
    int get_index(const point cell, const int width) {
        return cell.y * width + cell.x;
    }

    const map<string, point> moves = {{"UP",    {0,  -1}},
                                      {"DOWN",  {0,  1}},
                                      {"LEFT",  {-1, 0}},
                                      {"RIGHT", {1,  0}}};

    vector<point> find_hero_and_exit(const maze_data *maze) {
        point hero{}, exit{};
        size_t heroes_amount = 0, exits_amount = 0;
        for (auto &elem:maze->field)
            switch (elem.state) {
                case State::HERO:
                    hero.x = elem.x;
                    hero.y = elem.y;
                    hero.state = State::HERO;
                    heroes_amount++;
                    break;
                case State::EXIT:
                    exit.x = elem.x;
                    exit.y = elem.y;
                    exit.state = State::EXIT;
                    exits_amount++;
                    break;
                default:
                    break;
            }
        if (exits_amount != 1 || heroes_amount != 1)
            return vector<point>(0);
        vector<point> res;
        res.push_back(hero);
        res.push_back(exit);
        return res;
    }
};

vector<int> wave_motion(const maze_data *maze_data) {
    vector<bool> used(maze_data->height * maze_data->width, false);
    vector<int> wave_map(maze_data->height * maze_data->width);
    point hero{}, exit{};
    int i = 0;
    for (auto &elem: wave_map) {
        elem = static_cast<int>(maze_data->field[i].state);
        switch (maze_data->field[i].state) {
            case State::WALL:
                used[i] = true;
                break;
            case State::EMPTY:
            case State::HERO:
            case State::EXIT:
                break;
            default:
                return vector<int>(0);
        }
        i++;
    }
    vector<point> hero_and_exit = find_hero_and_exit(maze_data);
    vector<point> null = vector<point>(0);
    if (hero_and_exit == null)
        return vector<int>(0);
    hero = hero_and_exit[0];
    exit = hero_and_exit[1];
    queue<point> queue;
    queue.push(hero);
    used[get_index(hero, maze_data->width)] = true;
    wave_map[get_index(exit, maze_data->width)] = -1;
    while (!queue.empty()) {
        point cur = queue.front();
        queue.pop();
        for (const auto &move:moves) {
            point delta = move.second;
            point moved_cur{cur.x + delta.x, cur.y + delta.y};
            if (moved_cur.x >= 0 && moved_cur.x < maze_data->width &&
                moved_cur.y >= 0 && moved_cur.y < maze_data->height &&
                !used[get_index(moved_cur, maze_data->width)]) {
                queue.push({moved_cur.x, moved_cur.y});
                used[get_index(moved_cur, maze_data->width)] = true;
                wave_map[get_index(moved_cur, maze_data->width)] = wave_map[get_index(cur, maze_data->width)] + 1;
            }
        }
    }
    if (wave_map[get_index(exit, maze_data->width)] == -1)
        return vector<int>(0);
    return wave_map;
}

vector<point> find_path(vector<int> wave_map, const maze_data *maze) {
    vector<point> path;
    vector<point> hero_and_exit = find_hero_and_exit(maze);
    point hero = hero_and_exit[0];
    point exit = hero_and_exit[1];
    point cur = {exit.x, exit.y};
    path.push_back(cur);
    while (wave_map[get_index(cur, maze->width)] != static_cast<int>(State::HERO)) {
        for (const auto &move:moves) {
            point delta = move.second;
            point moved_cur{cur.x + delta.x, cur.y + delta.y};
            if (wave_map[get_index(moved_cur, maze->width)] == wave_map[get_index(cur, maze->width)] - 1) {
                cur = moved_cur;
                path.insert(path.begin(), cur);
                break;
            }
        }
    }
    assert(path.front().x == hero.x);
    assert(path.front().y == hero.y);
    return path;
}