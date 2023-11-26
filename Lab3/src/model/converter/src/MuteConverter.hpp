#pragma once

#include <converter/includes/IConverter.hpp>

namespace Converter {
    class MuteConverter : public IConverter {
    private:
        int m_start;
        int m_stop;

    public:
        std::vector<short> UpdateSound(std::vector<short> samples, unsigned int second) override;
        void PutParameters(std::vector<Params> params) override;
        std::string GetName() override;
        std::string GetParametrs() override;
        std::string GetFeatures() override;
        std::string GetSyntax() override;
    };
} // namespace Converter
