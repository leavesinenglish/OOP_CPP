#include "solution.hpp"
#include <cmath>

double solution::solve() {
    if (!is_valid()) {
        return nan("");
    }
    double prev = get_initial_value();
    for (size_t i = 0; i < number_of_iteration; ++i) {
        auto cur = get_next_value(prev);
        if (abs(cur) > epsilon && !std::isnormal(cur)) {
            break;
        }
        if (check_result(cur, prev)) {
            return cur;
        }
        prev = cur;
    }
    return nan("");
}