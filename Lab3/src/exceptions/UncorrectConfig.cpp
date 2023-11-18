#include "UncorrectConfig.hpp"

UncorrectConfig::UncorrectConfig(std::string text) { error = text; }
std::string UncorrectConfig::what() { return error; }