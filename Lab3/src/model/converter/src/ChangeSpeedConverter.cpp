#include "ChangeSpeedConverter.hpp"

namespace Converter {
    std::vector<unsigned short> ChangeSpeedConverter::UpdateSound(std::vector<unsigned short> samples, unsigned int second) {
        if (second < m_start || second > m_stop) {
            return samples;
        }
        std::vector<unsigned short> newSamples;
        for (float i = 0; i < 44100.0f; i += m_speedModifier) {
            newSamples.push_back(samples[static_cast<int>(floor(i))]);
        }
        return newSamples;
    }
    void ChangeSpeedConverter::putParametrs(std::pair<std::pair<int, int>, float> params) {
        m_start = params.first.first;
        m_stop = params.first.second;
        m_speedModifier = params.second;
    }
    std::string ChangeSpeedConverter::getName() { return "changeSpeed converter"; }
    std::string ChangeSpeedConverter::getParametrs() { return "start, stop, speed modifier"; }
    std::string ChangeSpeedConverter::getFeatures() { return "change speed in interval"; }
    std::string ChangeSpeedConverter::getSyntax() { return "change_speed <int> <int> <float>"; }
} // namespace Converter