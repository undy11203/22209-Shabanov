#include "MixConverter.hpp"

namespace Converter {
    std::vector<short> MixConverter::UpdateSound(std::vector<short> samples, unsigned int second) {
        if (second < m_startSec) {
            return samples;
        }

        std::vector<short> additionalSamples = m_additionalFile->GetCurrentSamples();
        for (size_t i = 0; i < samples.size(); i++) {
            samples[i] = (samples[i] + additionalSamples[i]) / 2;
        }

        return samples;
    }
    void MixConverter::PutParametrs(WavFileModel &wavFile, int start) {
        m_additionalFile.reset(&wavFile, [](WavFileModel const *) {});
        m_startSec = start;
    }
    std::string MixConverter::GetName() { return "Mix converter"; }
    std::string MixConverter::GetParametrs() { return "additional file, start second"; }
    std::string MixConverter::GetFeatures() { return "mix with additional sound with start second"; }
    std::string MixConverter::GetSyntax() { return "mix $<int> <int>"; }

} // namespace Converter