#pragma once

#include <string>
#include <vector>

#include <converter/includes/Fwd.hpp>
#include <converter/includes/IConverter.hpp>
#include <file/includes/ConfigFileModel.hpp>
#include <file/includes/WavFileModel.hpp>

class SoundController {
private:
    std::vector<Converter::IConverterPtr> m_vectConverters;
    ConfigFileModel m_configFileModel;
    WavFileModel m_outWavFileModel;
    std::vector<WavFileModel> m_vectInWavFileModel;

    bool InitConfConvertors();
    void InitForHelpListConvertors();

public:
    SoundController() = default;
    SoundController(std::vector<std::string> args);
    void FillConvertor(std::string command);
    void Convert();
    void PrintHelpList();
};
