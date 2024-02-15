#include "UncorrectConfig.hpp"

UncorrectConfig::UncorrectConfig(std::string text) { error = text; }
const char *UncorrectConfig::what() const noexcept { return error.data(); }