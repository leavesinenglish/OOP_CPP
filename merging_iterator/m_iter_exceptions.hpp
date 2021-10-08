#pragma once
#include <string>

class Merge_iterator_exception: std::exception{
public:
    virtual void Message(){};
};

class Out_of_range_exception final : Merge_iterator_exception{
    std::string m_error = "Out of range position was sent in function";
public:
    Out_of_range_exception()= default;;
    inline void Message() override{
        std::cerr<<m_error<<std::endl;
    }
};

class Cant_find_new_element final : Merge_iterator_exception{
    std::string m_error = "Out of range position was sent in function";
public:
    Cant_find_new_element()= default;;
    inline void Message() override{
        std::cerr<<m_error<<std::endl;
    }
};
