#include <string>
#include <sstream> 
#include <fstream>

#include "../includes/WordCounter.hpp"

bool SortCompare(WordData first, WordData second) {
    return first.count > second.count;
}

WordCounter::WordCounter(char* inputPath, char* outputPath) {
    this->inputPath = inputPath;
    this->outputPath = outputPath;
    this->allWordCount = 0;
}

std::list<WordData> WordCounter::SortStatistics(std::map<std::string, unsigned int> wordsStatistic) {
    std::list<WordData> wordList;
    
    for(auto wordStatistic: wordsStatistic) {
        WordData data;

        data.word = wordStatistic.first;
        data.count = wordStatistic.second;
        data.countPerSent = (double)data.count / (double)this->allWordCount * (double)100;

        wordList.push_back(data);
    }

    wordList.sort(SortCompare);

    return wordList;
}

// здесь будем подсчитывать слова, и allWords и конкретные
std::list<WordData> WordCounter::GetWordsStatistic() {
    std::fstream fs(this->inputPath);
    std::string line;
    std::map<std::string, unsigned int> wordMap;

    while(!fs.eof()) {
        std::getline(fs, line);
        for(size_t i = 0; i < line.length(); i++) {
            if(!(line[i] >= '0' && line[i] <= '9' || 
                 line[i] >= 'A' && line[i] <= 'Z' || 
                 line[i] >= 'a' && line[i] <= 'z' )) {
                line[i] = ' ';
            }
        }
        std::stringstream words(line);
        std::string word;
        while(words >> word) {
            wordMap[word]++;
            this->allWordCount++;
        }
    }

    std::list<WordData> wordsStatistic = this->SortStatistics(wordMap);
    return wordsStatistic;
}

void WordCounter::WriteWordsStatistic(std::list<WordData> wordsList) {
    std::fstream fs(this->outputPath);
    
    for(WordData word : wordsList) {
        fs << word.word << ", " << word.count << ", " << word.countPerSent << std::endl;
    }
}