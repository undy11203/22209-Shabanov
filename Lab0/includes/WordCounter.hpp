#include <iostream>
#include <string>
#include <list>
#include <map>

struct WordData {
    std::string word;
    unsigned int count;
    double countPerSent;
};

class WordCounter {
private:
    std::string inputPath;
    std::string outputPath;
    unsigned int allWordCount;

    std::list<WordData> SortStatistics(std::map<std::string, unsigned int> wordsStatistic);
public:
    WordCounter(char* inputPath, char* outputPath);

    std::list<WordData> GetWordsStatistic();
    
    void WriteWordsStatistic(std::list<WordData> wordsList);
};
