#include "operations.hpp"
#include "arithmetic_operations.hpp"

int Operations::execute(int leftNumber, const std::string &opSymbol, int rightNumber) const {
    if (operations.count(opSymbol) == 0) return 0;
    return operations.at(opSymbol)->execute(leftNumber, rightNumber);
}

const std::unique_ptr<Operations> &Operations::init_operation() {
    static std::unique_ptr<Operations> instance(new Operations);
    instance->add_operation(new Addition);
    instance->add_operation(new Subtraction);
    instance->add_operation(new Multiplication);
    instance->add_operation(new Division);
    return instance;
}

void Operations::add_operation(Arithmetic_operation_interface *op) {
    operations.emplace(op->get_operation_sign(), op);
}