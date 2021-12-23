#include "chord_method.hpp"
#include <cmath>

bool chord_method::check_result(double current, double previous) {
    func = function(current);
    return abs(func) < precision;
}

double chord_method::get_next_value(double current) {
    return current - (current - left_boundary) * func / (func - func_left_value);
}

double chord_method::get_initial_value() {
    func = function(right_boundary);
    return right_boundary;
}

bool chord_method::is_valid() {
    if (left_boundary > right_boundary || precision > 1 ||
        precision < 0 || left_boundary - right_boundary > epsilon ||
        right_boundary - left_boundary < -epsilon || function == nullptr) {
        return false;
    }
    func_left_value = function(left_boundary);
    if (std::isnan(func_left_value) || func_left_value * function(right_boundary) >= 0) {
        return false;
    }
    return true;
}