#include <fstream>
#include <iostream>
#include <string>

#include "CSVParser.tpp"
#include "TupleOutput.tpp"
#include "execptions/DataExecption.hpp"


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

    // CSVParser<int, float, char, std::string> parser(file, 0, '[', '8', 'i');

    // try {
    //     for (std::tuple<int, float, char, std::string> rs : parser) {
    //         std::cout << rs << std::endl;
    //     }
    // } catch (DataExecption &e) {
    //     std::cout << e.what() << std::endl;
    // }

    return 0;
}