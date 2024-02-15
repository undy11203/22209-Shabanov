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
        std::vector<short> UpdateSound(std::vector<short> &samples, unsigned int second) override;
        void PutParameters(std::vector<Params> params) override;
        std::string GetName() override;
        std::string GetParametrs() override;
        std::string GetFeatures() override;
        std::string GetSyntax() override;
    };
} // namespace Converter
