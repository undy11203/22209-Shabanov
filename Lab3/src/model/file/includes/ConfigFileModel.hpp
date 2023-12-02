#pragma once

#include <fstream>
#include <string>
#include <vector>

#include <converter/includes/Parametrs.hpp>
#include <file/includes/WavFileModel.hpp>

class ConfigFileModel {
private:
    std::string m_configPath;
    std::ifstream m_config;
    std::string m_currentLine;

public:
    ConfigFileModel();
    ConfigFileModel(std::string configPath);
    ConfigFileModel &operator=(const ConfigFileModel &other);
    void OpenConfig();
    void CloseConfig();
    std::string NextCommand();
    bool GetParam(std::string command, std::vector<Params> &params, std::vector<WavFileModel> &m_vectInWavFileModel);
    bool GetDuration(std::vector<Params> &param);
    bool GetTimePointAndAdditional(std::vector<Params> &param, std::vector<WavFileModel> &wavFiles);
    bool GetDurationAndModifier(std::vector<Params> &param);
};
