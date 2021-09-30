#pragma once
#include <string>

class OutOfRangeException final :std::exception
{
    std::string m_error = "Out of range position was sent in function";
public:
    OutOfRangeException() {}
    const char* what() noexcept { return m_error.c_str(); }
};