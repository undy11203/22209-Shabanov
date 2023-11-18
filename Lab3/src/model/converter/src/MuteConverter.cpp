#include "MuteConverter.hpp"

namespace Converter {
    std::vector<short> MuteConverter::UpdateSound(std::vector<short> samples, unsigned int second) {
        if (second < m_start || second > m_stop) {
            return samples;
        }

        for (auto &sample : samples) {
            sample = 0;
        }

        return samples;
    }
    void MuteConverter::PutParametrs(std::pair<int, int> param) {
        m_start = param.first;
        m_stop = param.second;
    }
    std::string MuteConverter::GetName() { return "Mute converter"; }
    std::string MuteConverter::GetParametrs() { return "start second, stop second"; }
    std::string MuteConverter::GetFeatures() { return "Mute in interval"; }
    std::string MuteConverter::GetSyntax() { return "mute <int> <int>"; }

} // namespace Converter
