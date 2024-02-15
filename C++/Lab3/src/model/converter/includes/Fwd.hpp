#pragma once

#include <memory>

namespace Converter {
    struct IConverter;
    using IConverterPtr = std::shared_ptr<IConverter>;
} // namespace Converter
