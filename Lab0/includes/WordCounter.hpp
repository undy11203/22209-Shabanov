#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H

#include <iostream>
#include <list>
#include <map>
#include <string>

struct WordData {
    std::string word;
    unsigned int count;
    double countPerSent;
};

class WordCounter {
  private:
    std::string inputPath_;
    std::string outputPath_;
    unsigned int allWordCount_;

    std::list<WordData>
    SortStatistics(std::map<std::string, unsigned int> wordsStatistic);

  public:
    WordCounter(std::string inputPath, std::string outputPath);

    std::list<WordData> GetWordsStatistic();

    void WriteWordsStatistic(std::list<WordData> wordsList);
};

#endif
