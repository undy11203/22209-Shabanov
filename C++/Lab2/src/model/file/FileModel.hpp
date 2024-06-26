#pragma once

#include <bitset>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

class FileModel {
private:
    std::filesystem::path m_inputPath;
    std::filesystem::path m_outputPath;
    std::vector<std::string> m_errorPoint;

    enum Type {
        IN,
        OUT
    };
    void CreateDefaultFile(std::string name, Type type);

public:
    FileModel() = default;
    FileModel(std::string inputPath, std::string outputPath);
    ~FileModel() = default;
    std::string GetNameUniveristyFromFile();
    std::pair<int, int> GetSizeFromFile();
    std::pair<std::bitset<8>, std::bitset<8>> GetRulesFromFile();
    std::vector<std::pair<int, int>> GetAliveFromFile();
    void SaveToFile(std::string name,
                    std::pair<std::bitset<8>, std::bitset<8>> rules,
                    std::vector<std::vector<bool>> map);
    bool isFileExists(std::string &filePath);
    std::vector<std::string> ErrorInPoint();
};
