#pragma once
#include "arithmetic_operation_interface.hpp"

class Addition final : public Arithmetic_operation_interface {
public:
    Addition() = default;
    ~Addition() override = default;
    [[nodiscard]] std::string get_operation_sign() const override {
        return "+";
    };
    [[nodiscard]] int execute(int left, int right) const override{
        return left + right;
    };
};

class Subtraction final : public Arithmetic_operation_interface {
public:
    Subtraction() = default;
    ~Subtraction() override = default;
    [[nodiscard]] std::string get_operation_sign() const override{
        return "-";
    };
    [[nodiscard]] int execute(int left, int right) const override{
        return left - right;
    };
};

class Multiplication final : public Arithmetic_operation_interface {
public:
    Multiplication() = default;
    ~Multiplication() override = default;
    [[nodiscard]] std::string get_operation_sign() const override{
        return "*";
    };
    [[nodiscard]] int execute(int left, int right) const override{
        return left * right;
    };
};

class Division final : public Arithmetic_operation_interface {
public:
    Division() = default;
    ~Division() override = default;
    [[nodiscard]] std::string get_operation_sign() const override{
        return "/";
    };
    [[nodiscard]] int execute(int left, int right) const override{
        return left / right;
    };
};