#include <fstream>
#include <sstream>

#include "exceptions/DataExecption.hpp"

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
        int countPoint = 0;
        for (const char &c : str) {
            if (!std::isdigit(c) && c != '.' || countPoint > 1) {
                return false;
            }
            if (countPoint == 0) {
                countPoint++;
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
        if (!IsInt(str) && !IsChar(str) && !IsFloat(str)) {
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
    class Iterator {
    private:
        friend class CSVParser<Args...>;
        Iterator(CSVParser<Args...> &p, bool isEndPoint) : value(p), isEndPoint(isEndPoint) {}

    public:
        bool isEndPoint;
        CSVParser &value;
        bool operator!=(Iterator const &other);
        std::tuple<Args...> operator*() const;
        Iterator &operator++();
    };

    std::ifstream m_file;
    std::tuple<Args...> m_tuple;
    std::string m_row;
    char m_delimCol = ',';
    char m_delimRow = '\n';
    char m_delimEscape = '\"';
    int m_fileStart = 0;

    int m_numberCurrentRow = 0;
    int m_numberCurrentCol = 0;

    void GetRow();
    void GetCell(std::istringstream &iss, std::string &str, const char &delimCol);

    template <typename T>
    T StrToTypeT(std::istringstream &iss);
    template <size_t... Is>
    void StrRowToTupleRow(std::index_sequence<Is...>);

public:
    CSVParser(std::ifstream &fileDesc, int count);
    CSVParser(std::ifstream &fileDesc, int count, char delimCol);
    CSVParser(std::ifstream &fileDesc, int count, char delimCol, char delimRow);
    CSVParser(std::ifstream &fileDesc, int count, char delimCol, char delimRow, char delimShield);

    Iterator begin();
    Iterator end();
};

template <typename... Args>
CSVParser<Args...>::CSVParser(std::ifstream &fileDesc, int count) : m_file(std::move(fileDesc)) {

    for (size_t i = 0; i < count; i++) {
        GetRow();
    }
    m_fileStart = m_file.tellg();
}

template <typename... Args>
CSVParser<Args...>::CSVParser(std::ifstream &fileDesc, int count, char delimCol) : m_file(std::move(fileDesc)), m_delimCol{delimCol} {
    for (size_t i = 0; i < count; i++) {
        GetRow();
    }
    m_fileStart = m_file.tellg();
}

template <typename... Args>
CSVParser<Args...>::CSVParser(std::ifstream &fileDesc, int count, char delimCol, char delimRow) : m_file(std::move(fileDesc)), m_delimCol{delimCol}, m_delimRow{delimRow} {
    for (size_t i = 0; i < count; i++) {
        GetRow();
    }
    m_fileStart = m_file.tellg();
}

template <typename... Args>
CSVParser<Args...>::CSVParser(std::ifstream &fileDesc, int count, char delimCol, char delimRow, char delimEscape) : m_file(std::move(fileDesc)), m_delimCol{delimCol}, m_delimRow{delimRow}, m_delimEscape{delimEscape} {
    for (size_t i = 0; i < count; i++) {
        GetRow();
    }
    m_fileStart = m_file.tellg();
}

template <typename... Args>
CSVParser<Args...>::Iterator CSVParser<Args...>::begin() {
    m_file.seekg(m_fileStart);
    GetRow();

    return Iterator(*this, false);
}

template <typename... Args>
CSVParser<Args...>::Iterator CSVParser<Args...>::end() {
    return Iterator(*this, true);
}

template <typename... Args>
void CSVParser<Args...>::GetRow() {
    m_numberCurrentRow++;
    m_row.clear();

    bool isEscaped = false;

    char c;
    while (m_file.get(c)) {

        if (c == m_delimEscape) {
            if (isEscaped) {
                m_row.append(1, c);
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
void CSVParser<Args...>::GetCell(std::istringstream &iss, std::string &str, const char &delimCol) {
    str.clear();

    bool isEscaped = false;

    char c;
    while (iss.get(c)) {
        if (c == m_delimEscape) {
            if (isEscaped) {
                str.append(1, c);
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
bool CSVParser<Args...>::Iterator::operator!=(Iterator const &other) {
    if (value.m_file.eof() && isEndPoint == false) {
        isEndPoint = true;
        return isEndPoint;
    }

    return !(isEndPoint);
}

template <typename... Args>
std::tuple<Args...> CSVParser<Args...>::Iterator::operator*() const {
    value.StrRowToTupleRow(std::index_sequence_for<Args...>{});
    return value.m_tuple;
}

template <typename... Args>
typename CSVParser<Args...>::Iterator &CSVParser<Args...>::Iterator::operator++() {
    value.GetRow();
    return *this;
}

template <typename... Args>
template <typename T>
T CSVParser<Args...>::StrToTypeT(std::istringstream &iss) {
    std::string stringValue;
    GetCell(iss, stringValue, m_delimCol);
    m_numberCurrentCol++;

    if constexpr (std::is_same<T, int>::value) {
        if (IsInt(stringValue)) {
            return std::stoi(stringValue);
        } else {
            throw DataExecption(m_numberCurrentCol, m_numberCurrentRow);
        }
    } else if constexpr (std::is_same<T, float>::value || std::is_same<T, double>::value) {
        if (IsFloat(stringValue)) {
            return std::stof(stringValue);
        } else {
            throw DataExecption(m_numberCurrentCol, m_numberCurrentRow);
        }
    } else if constexpr (std::is_same<T, char>::value) {
        if (IsChar(stringValue)) {
            return stringValue[0];
        } else {
            throw DataExecption(m_numberCurrentCol, m_numberCurrentRow);
        }
    } else if constexpr (std::is_same<T, std::string>::value) {
        if (IsString(stringValue)) {
            return stringValue;
        } else {
            throw DataExecption(m_numberCurrentCol, m_numberCurrentRow);
        }
    }

    return 0;
}

template <typename... Args>
template <size_t... Is>
void CSVParser<Args...>::StrRowToTupleRow(std::index_sequence<Is...>) {
    std::istringstream iss(m_row);

    ((std::get<Is>(m_tuple) = StrToTypeT<std::tuple_element_t<Is, decltype(m_tuple)>>(iss)), ...);
    m_numberCurrentCol = 0;
}
