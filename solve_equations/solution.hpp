#pragma once

#include <functional>

class solution {
protected:
    const size_t number_of_iteration = 1000000;

    const double left_boundary;
    const double right_boundary;
    const double precision;
    const std::function<double(double)> &function;
    const std::function<double(double)> &derivative;

    virtual void checkingFunctionExisting() {}

    virtual double get_next_value(double current) {
        return nan("");
    }

    virtual double get_initial_value() {
        return nan("");
    }

    virtual bool is_valid() {
        return false;
    }

    virtual bool check_result(double current, double previous);

public:

    explicit solution(const double left_boundary_, const double right_boundary_, const double precision_,
           const std::function<double(double)> &function_, const std::function<double(double)> &derivative_ = nullptr) :
                left_boundary(left_boundary_), right_boundary(right_boundary_),
                precision(precision_), function(function_), derivative(derivative_) {}

    double solve();
};