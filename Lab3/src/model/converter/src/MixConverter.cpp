#include "MixConverter.hpp"

#include "../includes/Parametrs.hpp"

namespace Converter {
    std::vector<short> MixConverter::UpdateSound(std::vector<short> samples, unsigned int second) {
        if (second < m_startSec) {
            return samples;
        }

        std::vector<short> additionalSamples = m_additionalFile->GetCurrentSamples();
        for (size_t i = 0; i < std::min(samples.size(), additionalSamples.size()); i++) {
            samples[i] = (samples[i] + additionalSamples[i]) / 2;
        }

        return samples;
    }
    void MixConverter::PutParameters(std::vector<Params> params) {
        m_additionalFile.reset(&std::get<AdditionalFile>(params[0]).wavFile, [](WavFileModel const *) {});
        m_startSec = std::get<TimePoint>(params[1]).sec;
    }
    std::string MixConverter::GetName() { return "Mix converter"; }
    std::string MixConverter::GetParametrs() { return "additional file, start second"; }
    std::string MixConverter::GetFeatures() { return "mix with additional sound with start second"; }
    std::string MixConverter::GetSyntax() { return "mix $<int> <int>"; }

} // namespace Converter