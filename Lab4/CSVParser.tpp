#pragma once

#include <fstream>
#include <sstream>

#include <iostream>

#include "execptions/DataExecption.hpp"

namespace {
    enum Shield {
        DelimColShield,
        DelimRowShield
    };

    bool IsInt(const std::string &str) {
        for (const char &c : str) {
            if (!std::isdigit(c)) {
                return false;
            }
        }
        return true;
    }
    bool IsFloat(const std::string &str) {
        for (const char &c : str) {
            if (!std::isdigit(c) && c != '.') {
                return false;
            }
        }
        return true;
    }
    bool IsChar(const std::string &str) {
        int i = 0;
        for (const char &c : str) {
            i++;
        }
        if (i == 1)
            return true;

        return false;
    }
    bool IsString(const std::string &str) {
        if (!IsInt(str) && !IsFloat(str) && !IsChar(str)) {
            return true;
        }
        return false;
    }

    void EscapeBeginSpace(std::string &str) {
        for (int i = 0; i < str.size(); i++) {
            if (str[i] != ' ') {
                str = str.substr(i);
                break;
            }
        }
    }

} // namespace

template <typename... Args>
class CSVParser {
private:
    std::ifstream m_fileDesc;
    int m_numberRow = 0;
    int m_numberCol = 0;
    std::string m_row;
    std::tuple<Args...> m_tuple;
    char m_delimCol = ',';
    char m_delimRow = '\n';
    char m_delimShield = '\"';
    bool m_end = false;

    class Iterator {
    private:
        friend class CSVParser<Args...>;

        Iterator(CSVParser<Args...> *p) : value(p) {}

    public:
        CSVParser *value;

        Iterator(const Iterator &other) : value(other.value) {}

        bool operator!=(Iterator const &other);

        std::tuple<Args...> operator*() const;

        Iterator &operator++(int);
        Iterator &operator++();
    };

public:
    Iterator iterator;

    CSVParser(std::ifstream &fileDesc, int count);
    CSVParser(std::ifstream &fileDesc, int count, char delimCol);
    CSVParser(std::ifstream &fileDesc, int count, char delimCol, char delimRow);
    CSVParser(std::ifstream &fileDesc, int count, char delimCol, char delimRow, char delimShield);

    void NextRow();
    void GetCol(std::istringstream &iss, std::string &str, const char &delimCol);

    Iterator begin();
    Iterator end();

    std::tuple<Args...> operator*();

    template <typename T>
    T GetCell(std::istringstream &iss) {
        std::string stringValue;
        GetCol(iss, stringValue, m_delimCol);
        m_numberCol++;

        if constexpr (std::is_same<T, int>::value) {
            if (IsInt(stringValue)) {
                return std::stoi(stringValue);
            } else {
                throw DataExecption(m_numberCol, m_numberRow);
            }
        } else if constexpr (std::is_same<T, float>::value || std::is_same<T, double>::value) {
            if (IsFloat(stringValue)) {
                return std::stof(stringValue);
            } else {
                throw DataExecption(m_numberCol, m_numberRow);
            }
        } else if constexpr (std::is_same<T, char>::value) {
            if (IsChar(stringValue)) {
                return stringValue[0];
            } else {
                throw DataExecption(m_numberCol, m_numberRow);
            }
        } else if constexpr (std::is_same<T, std::string>::value) {
            if (IsString(stringValue)) {
                return stringValue;
            } else {
                throw DataExecption(m_numberCol, m_numberRow);
            }
        }

        return 0;
    }

    template <size_t... Is>
    void StrRowToTupleRow(std::index_sequence<Is...>) {
        std::istringstream iss(m_row);

        ((std::get<Is>(m_tuple) = GetCell<std::tuple_element_t<Is, decltype(m_tuple)>>(iss)), ...);
        m_numberCol = 0;
    }
};

template <typename... Args>
CSVParser<Args...>::CSVParser(std::ifstream &fileDesc, int count) : iterator(this) {
    m_fileDesc = std::move(fileDesc);
    for (size_t i = 0; i < count; i++) {
        NextRow();
    }
}

template <typename... Args>
CSVParser<Args...>::CSVParser(std::ifstream &fileDesc, int count, char delimCol) : m_delimCol(delimCol), iterator(this) {
    m_fileDesc = std::move(fileDesc);
    for (size_t i = 0; i < count; i++) {
        NextRow();
    }
}

template <typename... Args>
CSVParser<Args...>::CSVParser(std::ifstream &fileDesc, int count, char delimCol, char delimRow) : m_delimCol(delimCol), m_delimRow(delimRow), iterator(this) {
    m_fileDesc = std::move(fileDesc);
    for (size_t i = 0; i < count; i++) {
        NextRow();
    }
}

template <typename... Args>
CSVParser<Args...>::CSVParser(std::ifstream &fileDesc, int count, char delimCol, char delimRow, char delimShield) : m_delimCol(delimCol), m_delimRow(delimRow), m_delimShield(delimShield), iterator(this) {
    m_fileDesc = std::move(fileDesc);
    for (size_t i = 0; i < count; i++) {
        NextRow();
    }
}

template <typename... Args>
void CSVParser<Args...>::NextRow() {
    m_numberRow++;
    m_row.clear();

    bool isEscaped = false;

    char c;
    while (m_fileDesc.get(c)) {
        if (c == m_delimShield) {
            if (isEscaped) {
                m_row.append(1, m_delimRow);
                isEscaped = false;
            } else {
                m_row.append(1, c);
                isEscaped = true;
            }
        } else if (c == m_delimRow && !isEscaped) {
            break;
        } else {
            m_row.append(1, c);
            isEscaped = false;
        }
    }
}

template <typename... Args>
void CSVParser<Args...>::GetCol(std::istringstream &iss, std::string &str, const char &delimCol) {
    str.clear();

    bool isEscaped = false;

    char c;
    while (iss.get(c)) {
        if (c == m_delimShield) {
            if (isEscaped) {
                str.append(1, m_delimCol);
                isEscaped = false;
            } else {
                isEscaped = true;
            }
        } else if (c == m_delimCol && !isEscaped) {
            break;
        } else {
            str.append(1, c);
            isEscaped = false;
        }
    }
    EscapeBeginSpace(str);
}

template <typename... Args>
typename CSVParser<Args...>::Iterator CSVParser<Args...>::begin() {
    NextRow();
    return Iterator(this);
}

template <typename... Args>
typename CSVParser<Args...>::Iterator CSVParser<Args...>::end() {
    return Iterator(this);
}

template <typename... Args>
bool CSVParser<Args...>::Iterator::operator!=(Iterator const &other) {
    if (value->m_fileDesc.eof() && value->m_end == false) {
        value->m_end = true;
        return value->m_end;
    }

    return !(value->m_end);
}

template <typename... Args>
std::tuple<Args...> CSVParser<Args...>::operator*() {
    StrRowToTupleRow(std::index_sequence_for<Args...>{});
    return m_tuple;
}

template <typename... Args>
std::tuple<Args...> CSVParser<Args...>::Iterator::operator*() const {
    return **value;
}

template <typename... Args>
typename CSVParser<Args...>::Iterator &CSVParser<Args...>::Iterator::operator++(int) {
    value->NextRow();
    return *this;
}

template <typename... Args>
typename CSVParser<Args...>::Iterator &CSVParser<Args...>::Iterator::operator++() {
    value->NextRow();
    return *this;
}