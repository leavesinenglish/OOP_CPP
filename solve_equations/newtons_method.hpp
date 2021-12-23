#pragma once

#include "solution.hpp"

class newton_method final : public solution {

    double split_ratio = 0;

    bool check_result(double current, double previous) override;

    double middle_of_interval(double left_boundary_, double right_boundary_);

    bool is_valid() override;

    double get_initial_value() override;

    double get_next_value(double current) override;

public:
    explicit newton_method(const double left_boundary_, const double right_boundary_,
                           const double precision_, const std::function<double(double)> &function_,
                           const std::function<double(double)> &derivative_)
            : solution(left_boundary_, right_boundary_, precision_, function_, derivative_) {}
};