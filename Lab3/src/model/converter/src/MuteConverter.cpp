#include "MuteConverter.hpp"

#include "../includes/Parametrs.hpp"

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
    void MuteConverter::PutParameters(std::vector<Params> params) {
        m_start = std::get<Duration>(params[0]).start;
        m_stop = std::get<Duration>(params[0]).stop;
    }
    std::string MuteConverter::GetName() { return "Mute converter"; }
    std::string MuteConverter::GetParametrs() { return "start second, stop second"; }
    std::string MuteConverter::GetFeatures() { return "Mute in interval"; }
    std::string MuteConverter::GetSyntax() { return "mute <int> <int>"; }

} // namespace Converter
