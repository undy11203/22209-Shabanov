#include "FormatExceptions.hpp"

FormatExceptions::FormatExceptions(std::string text) { error = text; };
const char *FormatExceptions::what() const noexcept { return error.data(); }
