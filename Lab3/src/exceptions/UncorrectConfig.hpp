#pragma once

#include <string>

class UncorrectConfig final : public std::exception {
private:
    std::string error;

public:
    UncorrectConfig(std::string text);
    const char *what() const noexcept override;
};
