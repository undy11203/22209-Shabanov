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
        void putParametrs(std::pair<std::pair<int, int>, float> params);
        std::string getName();
        std::string getParametrs();
        std::string getFeatures();
        std::string getSyntax();
    };
} // namespace Converter
