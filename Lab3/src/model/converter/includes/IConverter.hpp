#pragma once

#include "Parametrs.hpp"
#include <file/includes/WavFileModel.hpp>

#include <string>
#include <vector>

namespace Converter {
    struct IConverter {
    public:
        virtual ~IConverter() = default;
        virtual std::vector<short> UpdateSound(std::vector<short> samples, unsigned int second) = 0;
        virtual void PutParameters(std::vector<Params> params) = 0;
        virtual std::string GetName() = 0;
        virtual std::string GetParametrs() = 0;
        virtual std::string GetFeatures() = 0;
        virtual std::string GetSyntax() = 0;
    };
} // namespace Converter
