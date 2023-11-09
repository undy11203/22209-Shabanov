#include "FileModel.hpp"

#include <cstring>
#include <unordered_set>

namespace {
    struct pair_hash {
        std::size_t operator()(const std::pair<int, int> &v) const {
            return v.first * 31 + v.second;
        }
    };
} // namespace

FileModel::FileModel(std::string inputPath, std::string outputPath) {
    m_inputPath = strcmp(inputPath.data(), "") != 0
                      ? std::filesystem::path(inputPath)
                      : m_inputPath;
    m_outputPath = strcmp(outputPath.data(), "") != 0
                       ? std::filesystem::path(outputPath)
                       : m_outputPath;
}

std::string FileModel::GetNameUniveristyFromFile() {
    std::fstream fs(m_inputPath);
    std::string line;
    m_errorPoint.push_back("#N");
    while (std::getline(fs, line)) {
        if (line.find("#N") == 0) {
            m_errorPoint.pop_back();
            break;
        }
    }

    int startIndex = line.find(" ") + 1;
    int stopIndex = line.length();

    fs.close();

    return line.substr(startIndex, stopIndex - startIndex);
}
std::pair<int, int> FileModel::GetSizeFromFile() {
    std::pair<int, int> size;

    std::fstream fs(m_inputPath);
    std::string line;
    m_errorPoint.push_back("#S");
    while (std::getline(fs, line)) {
        if (line.find("#S") == 0) {
            m_errorPoint.pop_back();
            break;
        }
    }

    int startIndex = line.find(" ") + 1;
    int endIndex = line.find("/");
    size.first = std::stoi(line.substr(startIndex, endIndex - startIndex));

    startIndex = endIndex + 1;
    endIndex = line.length();
    size.second = std::stoi(line.substr(startIndex, endIndex - startIndex));

    fs.close();

    return size;
}

std::pair<std::bitset<8>, std::bitset<8>> FileModel::GetRulesFromFile() {
    std::bitset<8> birth;
    std::bitset<8> survive;
    std::pair<std::bitset<8>, std::bitset<8>> rule;

    std::fstream fs(m_inputPath);
    std::string line;
    m_errorPoint.push_back("#R");
    while (std::getline(fs, line)) {
        if (line.find("#R") == 0) {
            m_errorPoint.pop_back();
            break;
        }
    }

    int index = line.find("B") + 1;

    while (line[index] != '/') {
        birth |= 1 << line[index] - '0' - 1;
        index++;
    }

    index = line.find("S") + 1;

    while (index < line.length()) {
        survive |= 1 << line[index] - '0' - 1;
        index++;
    }

    rule.first = birth;
    rule.second = survive;

    fs.close();

    return rule;
}
std::vector<std::pair<int, int>> FileModel::GetAliveFromFile() {
    std::unordered_set<std::pair<int, int>, pair_hash> alive;
    std::vector<std::pair<int, int>> result;

    std::fstream fs(m_inputPath);
    std::string line;
    while (std::getline(fs, line)) {
        if (line.find("#") == std::string::npos)
            break;
    }

    do {
        std::pair<int, int> aliveCell;

        int startIndex = 0;
        int stopIndex = line.find(" ");
        aliveCell.first =
            std::stoi(line.substr(startIndex, stopIndex - startIndex + 1));

        startIndex = line.find(" ") + 1;
        stopIndex = line.length();
        aliveCell.second =
            std::stoi(line.substr(startIndex, stopIndex - startIndex));

        if (auto search = alive.find(aliveCell); search != alive.end()) {
            m_errorPoint.push_back(std::to_string(aliveCell.first) + "/" + std::to_string(aliveCell.second));
        } else {
            alive.insert(aliveCell);
        }

    } while (std::getline(fs, line));

    fs.close();

    result.insert(result.end(), alive.begin(), alive.end());
    return result;
}
void FileModel::SaveToFile(std::string name,
                           std::pair<std::bitset<8>, std::bitset<8>> rules,
                           std::vector<std::vector<bool>> map) {
    std::ofstream fs(m_outputPath);

    fs << "Name university: " << name << std::endl;
    fs << "Rules: B";
    for (size_t i = 0; i < rules.first.size(); i++) {
        fs << rules.first.test(i) ? std::to_string(i) : "";
    }
    fs << "/S";
    for (size_t i = 0; i < rules.second.size(); i++) {
        fs << rules.second.test(i) ? std::to_string(i) : "";
    }
    fs << std::endl;

    for (size_t i = 0; i < map[0].size(); i++) {
        fs << "==";
    }
    fs << "==" << std::endl;

    for (const std::vector<bool> &row : map) {
        fs << "|";
        for (bool cell : row) {
            fs << (cell ? "()" : "  ");
        }
        fs << "|";
        fs << std::endl;
    }

    for (size_t i = 0; i < map[0].size(); i++) {
        fs << "==";
    }
    fs << "==" << std::endl;
}

bool FileModel::isFileExists(std::string &filePath) {
    std::filesystem::path path(filePath);
    return std::filesystem::exists(path) &&
           std::filesystem::is_regular_file(path);
}

std::vector<std::string> FileModel::ErrorInPoint() {
    return m_errorPoint;
}