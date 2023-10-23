#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

class FileModel {
private:
    std::filesystem::path m_inputPath = "../assets/map/1.txt";
    std::filesystem::path m_outputPath = "../assets/out/1.txt";
    std::vector<std::string> m_errorPoint;

public:
    FileModel() = default;
    FileModel(std::string inputPath, std::string outputPath);
    ~FileModel() = default;
    std::string GetNameUniveristyFromFile();
    std::pair<int, int> GetSizeFromFile();
    std::pair<std::vector<int>, std::vector<int>> GetRulesFromFile();
    std::vector<std::pair<int, int>> GetAliveFromFile();
    void SaveToFile(std::string name,
                    std::pair<std::vector<int>, std::vector<int>> rules,
                    std::vector<std::vector<bool>> map);
    bool isFileExists(std::string &filePath);
    std::vector<std::string> ErrorInPoint();
};
