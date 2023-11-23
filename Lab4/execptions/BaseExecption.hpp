#pragma once
#include <string>

class BaseExecption {
protected:
    std::string m_error;

public:
    virtual std::string what() = 0;
};
