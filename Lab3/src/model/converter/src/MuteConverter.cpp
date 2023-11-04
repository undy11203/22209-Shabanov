#include "MuteConverter.hpp"

namespace Converter {
    std::vector<unsigned short> MuteConverter::UpdateSound(std::vector<unsigned short> samples, unsigned int second) {
        if (second < m_start || second > m_stop) {
            return samples;
        }

        for (auto &sample : samples) {
            sample = 0;
        }

        return samples;
    }
    void MuteConverter::putParametrs(std::pair<int, int> param) {
        m_start = param.first;
        m_stop = param.second;
    }
    std::string MuteConverter::getName() { return "Mute converter"; }
    std::string MuteConverter::getParametrs() { return "start second, stop second"; }
    std::string MuteConverter::getFeatures() { return "Mute in interval"; }
    std::string MuteConverter::getSyntax() { return "mute <int> <int>"; }

} // namespace Converter
