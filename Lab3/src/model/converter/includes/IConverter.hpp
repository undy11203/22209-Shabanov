#pragma once

#include <file/includes/WavFileModel.hpp>

#include <string>
#include <vector>

namespace Converter {
    struct IConverter {
    public:
        virtual ~IConverter() = default;
        virtual std::vector<unsigned short> UpdateSound(std::vector<unsigned short> samples, unsigned int second) = 0;
        virtual void putParametrs(std::pair<int, int> param) {}
        virtual void putParametrs(WavFileModel &wavFile, int start) {}
        virtual void putParametrs(std::pair<std::pair<int, int>, float> params) {}
        virtual std::string getName() = 0;
        virtual std::string getParametrs() = 0;
        virtual std::string getFeatures() = 0;
        virtual std::string getSyntax() = 0;
    };
} // namespace Converter
