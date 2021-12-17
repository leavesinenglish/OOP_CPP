#pragma once

#include <unordered_map>
#include <memory>
#include "arithmetic_operation_interface.hpp"


class Operations {
public:
    ~Operations() = default;
    [[nodiscard]] int execute(int leftNumber, const std::string &opSymbol, int rightNumber) const;
    static const std::unique_ptr<Operations>& init_operation();
    void add_operation(Arithmetic_operation_interface* op);

private:
    Operations() = default;
    std::unordered_map<std::string, std::unique_ptr<Arithmetic_operation_interface>> operations;
};
