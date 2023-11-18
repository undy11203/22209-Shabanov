#pragma once

#include <file/includes/WavFileModel.hpp>

#include <string>
#include <vector>

namespace Converter {
    struct IConverter {
    public:
        virtual ~IConverter() = default;
        virtual std::vector<short> UpdateSound(std::vector<short> samples, unsigned int second) = 0;
        virtual void PutParametrs(std::pair<int, int> param) {}
        virtual void PutParametrs(WavFileModel &wavFile, int start) {}
        virtual void PutParametrs(std::pair<std::pair<int, int>, float> params) {}
        virtual std::string GetName() = 0;
        virtual std::string GetParametrs() = 0;
        virtual std::string GetFeatures() = 0;
        virtual std::string GetSyntax() = 0;
    };
} // namespace Converter
