#include <functional>
#include <sstream>
#include <unordered_map>

#include "../includes/ConfigFileModel.hpp"

#include <UncorrectConfig.hpp>

namespace {
    bool ReadInStringStream(std::stringstream &words, std::string &arg) {
        if (!words.eof()) {
            words >> arg;
            return true;
        }
        return false;
    }

    bool IsInt(const std::string &str) {
        for (char c : str) {
            if (!std::isdigit(c)) {
                return false;
            }
        }
        return true;
    }

    bool IsIndex(const std::string &str) {
        if (str.empty() || str[0] != '$') {
            return false;
        }
        for (size_t i = 1; i < str.size(); ++i) {
            if (!std::isdigit(str[i])) {
                return false;
            }
        }
        return true;
    }

    bool IsFloat(const std::string &str) {
        for (char c : str) {
            if (!std::isdigit(c) && c != '.') {
                return false;
            }
        }
        return true;
    }
} // namespace

ConfigFileModel::ConfigFileModel() {}

ConfigFileModel::ConfigFileModel(std::string configPath) : m_configPath{configPath} {
}

ConfigFileModel &ConfigFileModel::operator=(const ConfigFileModel &other) {
    m_configPath = other.m_configPath;
    m_currentLine = other.m_currentLine;

    return *this;
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

bool ConfigFileModel::GetDuration(std::vector<Params> &param) {
    std::stringstream words(m_currentLine);
    std::string arg;
    ReadInStringStream(words, arg);

    Duration duration;

    if (!ReadInStringStream(words, arg)) {
        throw UncorrectConfig("Not enough arguments in command");
        return false;
    }

    if (IsInt(arg)) {
        duration.start = std::stoi(arg);
    } else {
        throw UncorrectConfig("No int on first arguments");
        return false;
    }

    if (!ReadInStringStream(words, arg)) {
        throw UncorrectConfig("Not enough arguments in command");
        return false;
    }

    if (IsInt(arg)) {
        duration.stop = std::stoi(arg);
    } else {
        throw UncorrectConfig("No int on second arguments");
        return false;
    }

    param.push_back(duration);

    return true;
}

bool ConfigFileModel::GetTimePointAndAdditional(std::vector<Params> &param, std::vector<WavFileModel> &wavFiles) {
    std::stringstream words(m_currentLine);
    std::string arg;

    AdditionalFile additionalFile = {.wavFile = wavFiles[0]};
    TimePoint timePoint;

    ReadInStringStream(words, arg);
    if (!ReadInStringStream(words, arg)) {
        throw UncorrectConfig("Not enough arguments in command");
        return false;
    }

    if (IsIndex(arg)) {
        int number = std::stoi(arg.substr(1));
        additionalFile.wavFile = wavFiles[number - 1];
    } else {
        throw UncorrectConfig("No index on first arguments");
        return false;
    }

    if (!ReadInStringStream(words, arg)) {
        throw UncorrectConfig("Not enough arguments in command");
        return false;
    }

    if (IsInt(arg)) {
        timePoint.sec = std::stoi(arg);
    } else {
        throw UncorrectConfig("No int on second arguments");
        return false;
    }

    param.push_back(additionalFile);
    param.push_back(timePoint);

    return true;
}
bool ConfigFileModel::GetDurationAndModifier(std::vector<Params> &param) {
    std::stringstream words(m_currentLine);

    std::string arg;

    Duration duration;
    Modifier modifier;

    if (!ReadInStringStream(words, arg)) {
        throw UncorrectConfig("No arguments in command");
        return false;
    }

    if (!ReadInStringStream(words, arg)) {
        throw UncorrectConfig("Not enough arguments in triplet");
        return false;
    }

    if (IsInt(arg)) {
        duration.start = std::stoi(arg);
    } else {
        throw UncorrectConfig("No int on first arguments");
        return false;
    }

    if (!ReadInStringStream(words, arg)) {
        throw UncorrectConfig("Not enough arguments in command");
        return false;
    }

    if (IsInt(arg)) {
        duration.stop = std::stoi(arg);
    } else {
        throw UncorrectConfig("No int on second arguments");
        return false;
    }

    if (!ReadInStringStream(words, arg)) {
        throw UncorrectConfig("Not enough arguments in command");
        return false;
    }

    if (IsFloat(arg)) {
        modifier.coefficient = std::stof(arg);
    } else {
        throw UncorrectConfig("No float on third arguments");
        return false;
    }

    param.push_back(duration);
    param.push_back(modifier);

    return true;
}
