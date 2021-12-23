#include "newtons_method.hpp"
#include <cmath>

bool newton_method::check_result(double current, double previous) {
    return abs(current - previous) < precision;
}

bool newton_method::is_valid() {
    if (left_boundary >= right_boundary || precision > 1 || precision < 0 || function == nullptr || derivative == nullptr) {
        return false;
    }
    double f_l = function(left_boundary);
    double f_r = function(right_boundary);
    if (std::isnan(f_l) || std::isnan(f_r) || f_l * f_r > 0) {
        return false;
    }
    return true;
}

double newton_method::get_next_value(double current) {
    double x = current;
    double g = derivative(x);
    if (abs(g) < 1e-20) {
        x = middle_of_interval(left_boundary, right_boundary);
        return x;
    }
    return (x - function(x) / g);
}

double newton_method::middle_of_interval(const double left_boundary_, const double right_boundary_) {
    split_ratio += 2;
    return right_boundary_ - (right_boundary_ - left_boundary_) / split_ratio;
}

double newton_method::get_initial_value() {
    return middle_of_interval(left_boundary, right_boundary);
}