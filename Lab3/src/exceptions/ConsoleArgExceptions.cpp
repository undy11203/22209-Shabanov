#include "ConsoleArgExceptions.hpp"

ConsoleArgExceptions::ConsoleArgExceptions(std::string text) { error = text; };
std::string ConsoleArgExceptions::what() { return error; }
