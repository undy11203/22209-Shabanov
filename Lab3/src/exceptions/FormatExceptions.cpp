#include "FormatExceptions.hpp"

FormatExceptions::FormatExceptions(std::string text) { error = text; };
std::string FormatExceptions::what() { return error; }
