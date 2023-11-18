#pragma once

#include <converter/includes/IConverter.hpp>

namespace Converter {
    class ChangeSpeedConverter : public IConverter {
    private:
        int m_start;
        int m_stop;
        float m_speedModifier;

    public:
        std::vector<short>
        UpdateSound(std::vector<short> samples, unsigned int second) override;
        void PutParametrs(std::pair<std::pair<int, int>, float> params);
        std::string GetName();
        std::string GetParametrs();
        std::string GetFeatures();
        std::string GetSyntax();
    };
} // namespace Converter
