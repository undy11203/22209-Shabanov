#pragma once

#include <string>

class BaseExceptions {
protected:
    std::string error;

public:
    virtual std::string what() = 0;
};
