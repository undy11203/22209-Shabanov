#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>

#include "../includes/WordCounter.hpp"


int main(int argc, char* argv[]) {
    WordCounter wordCounter(argv[1], argv[2]);

    std::list<WordData> wordsStatistic = wordCounter.GetWordsStatistic();

    wordCounter.WriteWordsStatistic(wordsStatistic);

    std::cout << "Done!";

    return 0;
}
