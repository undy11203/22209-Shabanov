#pragma once

#include <string>

class FormatExceptions final : public std::exception {
private:
    std::string error;

public:
    FormatExceptions(std::string text);
    const char *what() const noexcept override;
};