#pragma once
#include <string>

class Arithmetic_operation_interface {
public:
    Arithmetic_operation_interface() = default;
    virtual ~Arithmetic_operation_interface() = default;
    [[nodiscard]] virtual int execute(int left, int right) const = 0;
    [[nodiscard]] virtual std::string	get_operation_sign() const = 0;
};