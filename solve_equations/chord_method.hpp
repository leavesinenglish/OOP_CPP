#pragma once

#include "solution.hpp"

class chord_method final : public solution {
    double func_left_value = nan("");
    double func = 0.0;

    double get_initial_value() override;

    double get_next_value(double current) override;

    bool is_valid() override;

    bool check_result(double current, double previous) override;

public:
    explicit chord_method(const double left_boundary_, const double right_boundary_,
                          const double precision_, const std::function<double(double)> &function_):
            solution(left_boundary_, right_boundary_, precision_, function_) {}

};