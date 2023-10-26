#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <string>

#include "../includes/WordCounter.hpp"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Not enough arguments";
        return -1;
    }

    WordCounter wordCounter(argv[1], argv[2]);

    std::list<WordData> wordsStatistic = wordCounter.GetWordsStatistic();

    wordCounter.WriteWordsStatistic(wordsStatistic);

    std::cout << "Done!";

    return 0;
}
