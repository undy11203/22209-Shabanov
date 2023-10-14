#pragma once

#include <fstream>
#include <string>
#include <vector>

class FileModel {
private:
  std::string m_inputPath = "../assets/map/1.txt";
  std::string m_outputPath = "../assets/out/1.txt";

public:
  FileModel() = default;
  FileModel(std::string inputPath, std::string outputPath);
  ~FileModel() = default;
  std::string                       GetNameUniveristyFromFile();
  std::pair<int, int>               GetSizeFromFile();
  std::pair<std::vector<int>, 
            std::vector<int>>       GetRulesFromFile();
  std::vector<std::pair<int, int>>  GetAliveFromFile();
  void                              SaveToFile(std::vector<std::vector<bool>> map);
};
