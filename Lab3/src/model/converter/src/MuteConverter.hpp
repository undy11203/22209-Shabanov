#pragma once

#include <converter/includes/IConverter.hpp>

namespace Converter {
    class MuteConverter : public IConverter {
    private:
        int m_start;
        int m_stop;

    public:
        std::vector<short> UpdateSound(std::vector<short> samples, unsigned int second) override;
        void PutParametrs(std::pair<int, int> param);
        std::string GetName();
        std::string GetParametrs();
        std::string GetFeatures();
        std::string GetSyntax();
    };
} // namespace Converter
