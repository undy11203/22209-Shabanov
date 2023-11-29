#include <deque>

#include <iostream>

#include "../includes/WavFileModel.hpp"

namespace {
    void reverseShort(short &value) {
        value = (value >> 8) | (value << 8);
    }
    void reverseInt(unsigned int &value) {
        value = ((value >> 24) & 0xFF) | ((value >> 8) & 0xFF00) | ((value << 8) & 0xFF0000) | ((value << 24) & 0xFF000000);
    }

} // namespace

WavFileModel::WavFileModel() {}

WavFileModel::WavFileModel(std::string filePath) : m_filePath{filePath} {}

WavFileModel::~WavFileModel() {
}

void WavFileModel::OpenForRead() {
    m_wavFile = std::make_shared<std::fstream>(m_filePath, std::ios::binary | std::ios::in);
    std::deque<char> fourByte;
    char currentChar;
    for (size_t i = 0; i < 4; i++) {
        m_wavFile->get(currentChar);
        fourByte.push_back(currentChar);
    }
    if (fourByte[fourByte.size() - 1] == 'a' &&
        fourByte[fourByte.size() - 2] == 't' &&
        fourByte[fourByte.size() - 3] == 'a' &&
        fourByte[fourByte.size() - 4] == 'd') {
        return;
    }

    while (m_wavFile->get(currentChar)) {
        fourByte.pop_front();
        fourByte.push_back(currentChar);
        if (fourByte[fourByte.size() - 1] == 'a' &&
            fourByte[fourByte.size() - 2] == 't' &&
            fourByte[fourByte.size() - 3] == 'a' &&
            fourByte[fourByte.size() - 4] == 'd') {
            break;
        }
    }

    m_wavFile->read(reinterpret_cast<char *>(&m_dataSize), sizeof(m_dataSize));
    reverseInt(m_dataSize);
}
void WavFileModel::OpenForWrite() {
    m_wavFile = std::make_shared<std::fstream>(m_filePath, std::ios::binary | std::ios::out);
    unsigned int chunkId = 0x52494646;     // RIFF
    unsigned int chunkSize = 0;            // размер файла
    unsigned int format = 0x57415645;      // WAVE
    unsigned int subchunk1Id = 0x666d7420; // fmt
    unsigned int subchunk1Size = 16;       // PCM
    short audioFormat = 1;                 // PCM
    short numChannels = 1;                 // mono
    unsigned int sampleRate = 44100;       // 44100
    unsigned int byteRate = 44100 * 2;     // sample = 2 byte
    short blockAlign = 2;
    short bitsPerSample = 16;
    unsigned int subchunk2Id = 0x64617461; // data
    unsigned int subchunk2Size = 0;

    reverseInt(chunkId);       // big ending
    reverseInt(chunkSize);     // big ending
    reverseInt(format);        // big ending
    reverseInt(subchunk1Id);   // big ending
    reverseInt(subchunk2Id);   // big ending
    reverseInt(subchunk2Size); // big ending

    m_wavFile->write(reinterpret_cast<const char *>(&chunkId), sizeof(chunkId));
    m_wavFile->write(reinterpret_cast<const char *>(&chunkSize), sizeof(chunkSize));
    m_wavFile->write(reinterpret_cast<const char *>(&format), sizeof(format));
    m_wavFile->write(reinterpret_cast<const char *>(&subchunk1Id), sizeof(subchunk1Id));
    m_wavFile->write(reinterpret_cast<const char *>(&subchunk1Size), sizeof(subchunk1Size));
    m_wavFile->write(reinterpret_cast<const char *>(&audioFormat), sizeof(audioFormat));
    m_wavFile->write(reinterpret_cast<const char *>(&numChannels), sizeof(numChannels));
    m_wavFile->write(reinterpret_cast<const char *>(&sampleRate), sizeof(sampleRate));
    m_wavFile->write(reinterpret_cast<const char *>(&byteRate), sizeof(byteRate));
    m_wavFile->write(reinterpret_cast<const char *>(&blockAlign), sizeof(blockAlign));
    m_wavFile->write(reinterpret_cast<const char *>(&bitsPerSample), sizeof(bitsPerSample));
    m_wavFile->write(reinterpret_cast<const char *>(&subchunk2Id), sizeof(subchunk2Id));
    m_wavFile->write(reinterpret_cast<const char *>(&subchunk2Size), sizeof(subchunk2Size));
}

std::vector<short> WavFileModel::GetCurrentSamples() {
    return m_currentSamples;
}

unsigned int WavFileModel::GetSampleRate() {
    unsigned int res = 44100;
    return res;
}

unsigned int WavFileModel::GetDataSize() {
    return m_dataSize;
}

bool WavFileModel::IsEnd() {
    if (m_wavFile->peek() == EOF) {
        return true;
    }
    return false;
}

void WavFileModel::WriteSamples(std::vector<short> samples) {
    for (auto sample : samples) {
        m_wavFile->write(reinterpret_cast<const char *>(&sample), sizeof(sample));
    }
}

std::vector<short> WavFileModel::ReadSecond() {
    if (m_wavFile->peek() == EOF) {
        m_wavFile->seekg(44);
    }

    std::vector<short> samples;
    short sample;
    for (size_t i = 0; i < 44100; i++) {
        m_wavFile->read(reinterpret_cast<char *>(&sample), sizeof(sample));
        samples.push_back(sample);
    }

    m_currentSamples = samples;

    return samples;
}

void WavFileModel::CloseWriteFile() {
    m_wavFile->seekg(0, std::ios::end);
    m_dataSize = m_wavFile->tellg();

    unsigned int chunkSize = m_dataSize + 36;
    unsigned int subchunk2Size = m_dataSize;

    reverseInt(chunkSize);     // big ending
    reverseInt(subchunk2Size); // big ending

    m_wavFile->seekp(4, std::ios::beg);
    m_wavFile->write(reinterpret_cast<const char *>(&chunkSize), sizeof(chunkSize));

    m_wavFile->seekp(40, std::ios::beg);
    m_wavFile->write(reinterpret_cast<const char *>(&subchunk2Size), sizeof(subchunk2Size));

    m_wavFile->close();
}