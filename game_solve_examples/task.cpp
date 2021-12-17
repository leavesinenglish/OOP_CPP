#include "task.hpp"

Task::Task(int _firstNumber, int _secondNumber, const std::string & _operationSymbol)
{
    firstNumber = _firstNumber;
    secondNumber = _secondNumber;
    operationSymbol = _operationSymbol;
    result = Operations::init_operation()->execute(_firstNumber, _operationSymbol, _secondNumber);
}

std::string Task::show()
{
    return (std::to_string(firstNumber) + " " + operationSymbol + " " + std::to_string(secondNumber) + " = ");
}