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
    std::vector<short> m_currentSamples;
    unsigned int m_start;

public:
    WavFileModel();
    WavFileModel(std::string filePath);
    ~WavFileModel();
    void OpenForRead();
    void OpenForWrite();
    std::vector<short> GetCurrentSamples();
    std::vector<short> GetSamplesInSecond(int second);
    unsigned int GetSampleRate();
    unsigned int GetDataSize();
    bool IsEnd();
    void WriteSamples(std::vector<short> samples);
    std::vector<short> ReadSecond();
    void CloseWriteFile();
};
