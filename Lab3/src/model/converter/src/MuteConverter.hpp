#pragma once

#include <converter/includes/IConverter.hpp>

namespace Converter {
    class MuteConverter : public IConverter {
    private:
        int m_start;
        int m_stop;

    public:
        std::vector<unsigned short> UpdateSound(std::vector<unsigned short> samples, unsigned int second) override;
        void putParametrs(std::pair<int, int> param);
        std::string getName();
        std::string getParametrs();
        std::string getFeatures();
        std::string getSyntax();
    };
} // namespace Converter
