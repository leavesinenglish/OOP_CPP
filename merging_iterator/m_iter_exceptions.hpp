#pragma once
#include <string>

class Out_of_range_exception final : std::exception {
    std::string error = "Out of range position was sent in function";
public:
    Out_of_range_exception()= default;
    const char* print_error() noexcept { return error.c_str(); }
};