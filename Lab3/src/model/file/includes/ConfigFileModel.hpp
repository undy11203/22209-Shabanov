#pragma once

#include <fstream>
#include <string>
#include <vector>

class ConfigFileModel {
private:
    std::string m_configPath;
    std::ifstream m_config;
    std::string m_currentLine;

public:
    ConfigFileModel();
    ConfigFileModel(std::string configPath);
    ConfigFileModel &operator=(const ConfigFileModel &other);
    ~ConfigFileModel();
    void OpenConfig();
    void CloseConfig();
    std::string NextCommand();
    bool GetPairIndexInt(std::pair<int, int> &param);
    bool GetPairIntInt(std::pair<int, int> &param);
    bool GetTripletIntIntFloat(std::pair<std::pair<int, int>, float> &param);
};
