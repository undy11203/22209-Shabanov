#pragma once

#include "BaseExecption.hpp"

#include <string>

class DataExecption : public BaseExecption {
public:
    DataExecption(int col, int row);
    ~DataExecption();
    std::string what() override;
};

DataExecption::DataExecption(int col, int row) {
    m_error = "Error in col" + std::to_string(col) + "in row" + std::to_string(row);
}

std::string DataExecption::what() {
    return m_error;
}
