#include <fstream>
#include <iostream>
#include <string>

#include "CSVParser.tpp"

int main() {
    std::ifstream file("../test.csv");

    CSVParser<int, std::string> parser(file, 0);

    // std::tuple<float, int, std::string, int> tup(0.4, 10, "yes", 9);
    // std::cout << tup;

    for (std::tuple<int, std::string> rs : parser) {
        std::cout << rs << std::endl;
    }

    return 0;
}