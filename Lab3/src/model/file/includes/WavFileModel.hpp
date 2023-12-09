#pragma once

#include <fstream>
#include <memory>
#include <string>
#include <vector>

class WavFileModel {
private:
    std::string m_filePath;
    std::shared_ptr<std::fstream> m_wavFile;
    unsigned int m_dataSize;
    unsigned int m_start;

public:
    WavFileModel() = default;
    WavFileModel(std::string filePath);
    void OpenForRead();
    void OpenForWrite();
    std::vector<short> GetSamplesInSecond(int second);
    bool IsEnd();
    void WriteSamples(std::vector<short> samples);
    std::vector<short> ReadSecond();
    void CloseWriteFile();
};
