#include "FileModel.hpp"

#include <iostream>
#include <cstring>

FileModel::FileModel(std::string inputPath, std::string outputPath){
  m_inputPath = strcmp(inputPath.data(), "") != 0 ? std::filesystem::path(inputPath) : m_inputPath;
  m_outputPath = strcmp(outputPath.data(), "") != 0 ? std::filesystem::path(outputPath) : m_outputPath;
}

std::string FileModel::GetNameUniveristyFromFile() {
  std::fstream fs(m_inputPath);
  std::string line;
  std::getline(fs, line);
  std::getline(fs, line);

  int startIndex = line.find(" ") + 1;
  int stopIndex = line.length();

  fs.close();

  return line.substr(startIndex, stopIndex - startIndex);
}
std::pair<int, int> FileModel::GetSizeFromFile() {
  std::pair<int, int> size;

  std::fstream fs(m_inputPath);
  std::string line;
  std::getline(fs, line);
  std::getline(fs, line);
  std::getline(fs, line);
  std::getline(fs, line);

  int startIndex = line.find(" ") + 1;
  int endIndex = line.find("/");
  size.first = std::stoi(line.substr(startIndex, endIndex - startIndex));

  startIndex = endIndex + 1;
  endIndex = line.length();
  size.second = std::stoi(line.substr(startIndex, endIndex - startIndex));

  fs.close();

  return size;
}

std::pair<std::vector<int>, std::vector<int>> FileModel::GetRulesFromFile() {
  std::vector<int> birth;
  std::vector<int> survive;
  std::pair<std::vector<int>, std::vector<int>> rule;

  std::fstream fs(m_inputPath);
  std::string line;
  std::getline(fs, line);
  std::getline(fs, line);
  std::getline(fs, line);

  int index = line.find("B") + 1;

  while (line[index] != '/') {
    birth.push_back(line[index] - '0');
    index++;
  }

  index = line.find("S") + 1;

  while (index < line.length()) {
    survive.push_back(line[index] - '0');
    index++;
  }

  rule.first = birth;
  rule.second = survive;

  fs.close();

  return rule;
}
std::vector<std::pair<int, int>> FileModel::GetAliveFromFile() {
  std::vector<std::pair<int, int>> alive;

  std::fstream fs(m_inputPath);
  std::string line;
  std::getline(fs, line);
  std::getline(fs, line);
  std::getline(fs, line);
  std::getline(fs, line);

  while (std::getline(fs, line)) {
    std::pair<int, int> aliveCell;

    int startIndex = 0;
    int stopIndex = line.find(" ");
    aliveCell.first =
        std::stoi(line.substr(startIndex, stopIndex - startIndex + 1));

    startIndex = line.find(" ") + 1;
    stopIndex = line.length();
    aliveCell.second =
        std::stoi(line.substr(startIndex, stopIndex - startIndex));

    alive.push_back(aliveCell);
  }

  fs.close();

  return alive;
}
void FileModel::SaveToFile(std::vector<std::vector<bool>> map) {
  std::ofstream fs(m_outputPath);
  for (size_t i = 0; i < map[0].size(); i++)
  {
    fs << "==";
  }
  fs << "==\n";
  
  for (const std::vector<bool> &row : map) {
    fs << "|";
    for (bool cell : row) {
      fs << (cell ? "()" : "  ");
    }
    fs << "|";
    fs << '\n';
  }

  for (size_t i = 0; i < map[0].size(); i++)
  {
    fs << "==";
  }
  fs << "==\n";
}

bool FileModel::isFileExists(std::string& filePath) {
    std::filesystem::path path(filePath);
    return std::filesystem::exists(path) && std::filesystem::is_regular_file(path);
}