#include "ChangeSpeedConverter.hpp"

#include <math.h>

namespace Converter {
    std::vector<short> ChangeSpeedConverter::UpdateSound(std::vector<short> samples, unsigned int second) {
        if (second < m_start || second > m_stop) {
            return samples;
        }
        std::vector<short> newSamples;
        for (float i = 0; i < static_cast<float>(samples.size()); i += m_speedModifier) {
            newSamples.push_back(samples[static_cast<int>(floor(i))]);
        }
        return newSamples;
    }
    void ChangeSpeedConverter::PutParametrs(std::pair<std::pair<int, int>, float> params) {
        m_start = params.first.first;
        m_stop = params.first.second;
        m_speedModifier = params.second;
    }
    std::string ChangeSpeedConverter::GetName() { return "changeSpeed converter"; }
    std::string ChangeSpeedConverter::GetParametrs() { return "start, stop, speed modifier"; }
    std::string ChangeSpeedConverter::GetFeatures() { return "change speed in interval"; }
    std::string ChangeSpeedConverter::GetSyntax() { return "change_speed <int> <int> <float>"; }
} // namespace Converter