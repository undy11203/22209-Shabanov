#pragma once

#include <fstream>
#include <sstream>

#include <iostream>

namespace {
    bool IsInt(const std::string &str) {
        for (char c : str) {
            if (!std::isdigit(c)) {
                return false;
            }
        }
        return true;
    }
    bool IsFloat(const std::string &str) {
        for (char c : str) {
            if (!std::isdigit(c) && c != '.') {
                return false;
            }
        }
        return true;
    }
    bool IsChar(const std::string &str) {
        int i = 0;
        for (char c : str) {
            i++;
        }
        if (i == 1)
            return true;

        return false;
    }
    bool IsString(const std::string &str) {
        for (char c : str) {
            if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
                return true;
            }
        }
        return false;
    }
} // namespace

template <typename Ch, typename Tr, typename Tuple, size_t... Is>
void Print(std::basic_ostream<Ch, Tr> &os, const Tuple &t, std::index_sequence<Is...>) {
    ((os << (Is == 0 ? "{ " : ", ") << std::get<Is>(t) << (Is == sizeof...(Is) - 1 ? " }" : "")), ...);
}

template <typename Ch, typename Tr, typename... Args>
auto &operator<<(std::basic_ostream<Ch, Tr> &os, std::tuple<Args...> const &t) {
    Print(os, t, std::index_sequence_for<Args...>{});
    return os;
}

template <typename... Args>
class CSVParser {
private:
    std::ifstream m_fileDesc;
    std::string m_row;
    std::tuple<Args...> m_tuple;
    char m_delimCol = ',';
    char m_delimRow = '\n';

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

    void NextRow();

    Iterator begin();
    Iterator end();

    std::tuple<Args...> operator*();

    template <typename T>
    T GetCell(std::istringstream &iss) {
        std::string stringValue;
        std::getline(iss, stringValue, m_delimCol);

        if constexpr (std::is_same<T, int>::value) {
            if (IsInt(stringValue)) {
                return std::stoi(stringValue);
            }
        } else if constexpr (std::is_same<T, float>::value || std::is_same<T, double>::value) {
            if (IsFloat(stringValue)) {
                return std::stof(stringValue);
            }
        } else if constexpr (std::is_same<T, char>::value) {
            if (IsChar(stringValue)) {
                return stringValue.c_str();
            }
        } else if constexpr (std::is_same<T, std::string>::value) {
            if (IsString(stringValue)) {
                return stringValue;
            }
        } else {
        }

        return 0;
    }

    template <size_t... Is>
    void StrRowToTupleRow(std::index_sequence<Is...>) {
        std::istringstream iss(m_row);

        ((std::get<Is>(m_tuple) = GetCell<std::tuple_element_t<Is, decltype(m_tuple)>>(iss)), ...);
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
void CSVParser<Args...>::NextRow() {
    std::getline(m_fileDesc, m_row, m_delimRow);
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
    return !(value->m_fileDesc.eof());
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