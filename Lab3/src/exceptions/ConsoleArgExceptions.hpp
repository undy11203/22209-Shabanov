#pragma once

#include <BaseExceptions.hpp>

class ConsoleArgExceptions final : public BaseExceptions {
public:
    ConsoleArgExceptions(std::string text);
    std::string what() override;
};
