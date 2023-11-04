#include <sstream>

#include "../includes/ConfigFileModel.hpp"

ConfigFileModel::ConfigFileModel() {}

ConfigFileModel::ConfigFileModel(std::string configPath) : m_configPath{configPath} {
}

ConfigFileModel &ConfigFileModel::operator=(const ConfigFileModel &other) {
    m_configPath = other.m_configPath;
    m_currentLine = other.m_currentLine;

    return *this;
}

ConfigFileModel::~ConfigFileModel() {
}

void ConfigFileModel::OpenConfig() {
    m_config.open(m_configPath);
}
void ConfigFileModel::CloseConfig() {
    m_config.close();
}

std::string ConfigFileModel::NextCommand() {
    for (; std::getline(m_config, m_currentLine);) {
        if (m_currentLine[0] != '#') {
            std::stringstream words(m_currentLine);
            std::string command;
            words >> command;

            return command;
        }
    }
    return "\0";
}

std::pair<int, int> ConfigFileModel::getPairParametrs() {
    std::pair<int, int> pairParametrs;
    std::stringstream words(m_currentLine);
    std::string arg;
    words >> arg;
    words >> arg;

    if (arg[0] != '$') {
        pairParametrs.first = std::stoi(arg);
    } else {
        pairParametrs.first = std::stoi(arg.substr(1));
    }
    words >> arg;
    pairParametrs.second = std::stoi(arg);

    return pairParametrs;
}

std::pair<std::pair<int, int>, float> ConfigFileModel::getTripletParametrs() {
    std::pair<std::pair<int, int>, float> tripletParametrs;
    std::stringstream words(m_currentLine);
    std::string arg;
    words >> arg;
    words >> arg;
    tripletParametrs.first.first = std::stoi(arg);

    words >> arg;
    tripletParametrs.first.second = std::stoi(arg);

    words >> arg;
    tripletParametrs.second = std::stof(arg);

    return tripletParametrs;
}