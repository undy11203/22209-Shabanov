#pragma once

#include <string>

class DataExecption : public std::exception {
protected:
    std::string m_error;

public:
    explicit DataExecption(int col, int row);
    char const *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};

DataExecption::DataExecption(int col, int row) {
    m_error = "Line: " + std::to_string(row) + " Col: " + std::to_string(col) + " - uncorrect format data";
}

char const *DataExecption::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW {
    return m_error.data();
}
