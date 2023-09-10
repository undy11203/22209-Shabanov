#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "../includes/WordCounter.hpp"

namespace {
bool SortCompare(WordData first, WordData second) {
    return first.count > second.count;
}
} // namespace

WordCounter::WordCounter(std::string inputPath, std::string outputPath)
    : inputPath_{inputPath}, outputPath_{outputPath}, allWordCount_{0} {}

std::list<WordData> WordCounter::SortStatistics(
    std::map<std::string, unsigned int> wordsStatistic) {
    std::list<WordData> wordList;

    for (const auto &wordStatistic : wordsStatistic) {
        WordData data{.word = wordStatistic.first,
                      .count = wordStatistic.second,
                      .countPerSent = static_cast<double>(data.count) /
                                      static_cast<double>(allWordCount_) *
                                      100.};

        wordList.push_back(data);
    }

    wordList.sort(SortCompare);

    return wordList;
}

// здесь будем подсчитывать слова, и allWords и конкретные
std::list<WordData> WordCounter::GetWordsStatistic() {
    std::fstream fs(inputPath_);
    std::string line;
    std::map<std::string, unsigned int> wordMap;

    while (std::getline(fs, line)) {
        for (size_t i = 0; i < line.length(); i++) {
            if (!(line[i] >= '0' && line[i] <= '9' ||
                  line[i] >= 'A' && line[i] <= 'Z' ||
                  line[i] >= 'a' && line[i] <= 'z')) {
                line[i] = ' ';
            }
        }
        std::stringstream words(line);
        std::string word;
        while (words >> word) {
            wordMap[word]++;
            allWordCount_++;
        }
    }

    std::list<WordData> wordsStatistic = this->SortStatistics(wordMap);
    return wordsStatistic;
}

void WordCounter::WriteWordsStatistic(std::list<WordData> wordsList) {
    std::fstream fs(outputPath_);

    for (WordData word : wordsList) {
        fs << word.word << ", " << word.count << ", " << word.countPerSent
           << std::endl;
    }
}