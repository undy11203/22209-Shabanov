#include "MixConverter.hpp"

namespace Converter {
    std::vector<short> MixConverter::UpdateSound(std::vector<short> samples, unsigned int second) {
        if (second < m_startSec) {
            return samples;
        }

        std::vector<short> additionalSamples = m_additionalFile->getCurrentSamples();
        for (size_t i = 0; i < samples.size(); i++) {
            samples[i] = (samples[i] + additionalSamples[i]) / 2;
        }

        return samples;
    }
    void MixConverter::putParametrs(WavFileModel &wavFile, int start) {
        m_additionalFile.reset(&wavFile, [](WavFileModel const *) {});
        m_startSec = start;
    }
    std::string MixConverter::getName() { return "Mix converter"; }
    std::string MixConverter::getParametrs() { return "additional file, start second"; }
    std::string MixConverter::getFeatures() { return "mix with additional sound with start second"; }
    std::string MixConverter::getSyntax() { return "mix $<int> <int>"; }

} // namespace Converter