#pragma once

#include <memory>
#include <string>

#include <converter/includes/IConverter.hpp>

namespace Converter {
    class MixConverter : public IConverter {
    private:
        std::shared_ptr<WavFileModel> m_additionalFile;
        int m_startSec;

    public:
        std::vector<short> UpdateSound(std::vector<short> samples, unsigned int second) override;
        void putParametrs(WavFileModel &wavFile, int start);
        std::string getName();
        std::string getParametrs();
        std::string getFeatures();
        std::string getSyntax();
    };
} // namespace Converter
