#pragma once
#include <string>
#include "operations.hpp"

struct Task {
    Task() = default;
    Task(int _firstNumber, int _secondNumber, const std::string & _operationSymbol);
    int firstNumber = 0;
    int secondNumber = 0;
    int result = 0;
    std::string operationSymbol;
    std::string show();
};