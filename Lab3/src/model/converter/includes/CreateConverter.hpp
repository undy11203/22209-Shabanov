#pragma once

#include "Fwd.hpp"

#include <string>

namespace Converter {
    IConverterPtr createConverter(const std::string &name);
} // namespace Converter
