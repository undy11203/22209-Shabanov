#pragma once

#include <BaseExceptions.hpp>

class FormatExceptions final : public BaseExceptions {
public:
    FormatExceptions(std::string text);
    std::string what() override;
};