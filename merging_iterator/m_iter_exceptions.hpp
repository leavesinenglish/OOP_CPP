#pragma once
#include <string>

class OutOfRangeException final :std::exception{
    std::string m_error = "Out of range position was sent in function";
public:
    OutOfRangeException()= default;;
    inline void Message(){
        std::cerr<<m_error<<std::endl;
    }
};