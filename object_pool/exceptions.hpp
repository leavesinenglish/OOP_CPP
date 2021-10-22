#pragma once

class Exceptions : std::exception {
private:
    std::string m_error;
public:
    explicit Exceptions(std::string error) : m_error(error) {}

    const char *what() const noexcept override {
        return m_error.c_str();
    }
};