#pragma once

#include "BaseExceptions.hpp"

class UncorrectConfig final : public BaseExceptions {
public:
    UncorrectConfig(std::string text);
    std::string what() override;
};
