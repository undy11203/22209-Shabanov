#include <fstream>
#include <iostream>
#include <string>

#include <vector>

#include "CSVParser.tpp"
#include "TupleOutput.hpp"
#include "exceptions/DataExecption.hpp"

int main() {
    std::ifstream file("../test.csv");

    CSVParser<int, std::string> parser(file, 0);

    try {
        for (std::tuple<int, std::string> rs : parser) {
            std::cout << rs << std::endl;
        }
    } catch (DataExecption &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}