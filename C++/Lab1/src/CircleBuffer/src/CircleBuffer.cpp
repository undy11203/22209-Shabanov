#include <stdexcept>

#include <iostream>

#include "../includes/CircleBuffer.hpp"

namespace {
int mod(const int a, const int b) { return b > 0 ? (a % b + b) % b : 0; }
} // namespace

CircularBuffer::CircularBuffer()
    : m_capacity{0}, m_buffer{nullptr}, m_start{0}, m_end{0}, m_isEmpty{true} {}

CircularBuffer::CircularBuffer(const CircularBuffer &cb)
    : m_capacity{cb.m_capacity}, m_start{cb.m_start}, m_end{cb.m_end},
      m_isEmpty{cb.m_isEmpty} {
    m_buffer = new value_type[m_capacity];
    for (int i = 0; i < m_capacity; i++) {
        m_buffer[i] = cb.m_buffer[i];
    }
}

CircularBuffer::CircularBuffer(int capacity)
    : m_capacity{capacity}, m_start{0}, m_end{0}, m_isEmpty{true} {
    m_buffer = new value_type[capacity];
}

CircularBuffer::CircularBuffer(int capacity, const value_type &elem)
    : m_capacity{capacity}, m_start{0}, m_end{0}, m_isEmpty{false} {
    m_buffer = new value_type[capacity];

    for (size_t i = 0; i < m_capacity; i++) {
        m_buffer[i] = elem;
    }
}

CircularBuffer::~CircularBuffer() { delete[] m_buffer; }

value_type &CircularBuffer::operator[](int i) {
    int index = mod(m_start + i, m_capacity);
    return m_buffer[index];
}

const value_type &CircularBuffer::operator[](int i) const {
    int index = mod(m_start + i, m_capacity);
    return m_buffer[index];
}

value_type &CircularBuffer::at(int i) {
    if (i > size() - 1 || i < 0)
        throw std::out_of_range("Array index out of bounds");
    int index = mod(m_start + i, m_capacity);
    return m_buffer[index];
}

const value_type &CircularBuffer::at(int i) const {
    if (i > size() - 1 || i < 0)
        throw std::out_of_range("Array index out of bounds");
    int index = mod(m_start + i, m_capacity);
    return m_buffer[index];
}

value_type &CircularBuffer::front() { return m_buffer[m_start]; }

const value_type &CircularBuffer::front() const { return m_buffer[m_start]; }

value_type &CircularBuffer::back() {
    return m_buffer[mod(m_end - 1, m_capacity)];
}

const value_type &CircularBuffer::back() const {
    return m_buffer[mod(m_end - 1, m_capacity)];
}

value_type *CircularBuffer::linearize() {
    value_type *tmp = new value_type[m_capacity];
    for (int i = 0; i < size(); i++) {
        tmp[i] = at(i);
    }
    delete[] m_buffer;
    m_buffer = tmp;
    m_end = mod(size(), m_capacity);
    m_start = 0;
    return m_buffer;
}

bool CircularBuffer::is_linearized() const { return m_start == 0; }

void CircularBuffer::rotate(int new_begin) {
    new_begin = mod(new_begin, size());
    value_type* tmp = new value_type[m_capacity];
    for (size_t i = 0; i < size(); i++) {
        tmp[i] = at(mod(new_begin + i, size()));
    }
    delete[] m_buffer;
    m_end = mod(size(), m_capacity);
    m_start = 0;
    m_buffer = tmp;
}

int CircularBuffer::size() const {
    if (m_isEmpty) {
        return 0;
    }
    int lastIndex = mod(m_end - 1, m_capacity);

    int size = 0;
    if (lastIndex >= m_start) {
        size = lastIndex - m_start + 1;
    } else {
        size = m_capacity - (m_start - lastIndex) + 1;
    }
    return size;
}

bool CircularBuffer::empty() const { return size() == 0; }

bool CircularBuffer::full() const { return size() == capacity(); }

int CircularBuffer::reserve() const { return m_capacity - size(); }

int CircularBuffer::capacity() const { return m_capacity; }

void CircularBuffer::set_capacity(int new_capacity) {
    linearize();
    value_type *tmp = new value_type[new_capacity];

    if (new_capacity < m_capacity) {
        m_end = 0;
        m_isEmpty = new_capacity == 0 ? true : m_isEmpty;
        for (size_t i = 0; i < size(); i++) {
            tmp[i] = m_buffer[i];
        }
    } else {
        for (size_t i = 0; i < size(); i++) {
            tmp[i] = m_buffer[i];
        }
    }
    m_capacity = new_capacity;
    delete[] m_buffer;
    m_buffer = tmp;
}

void CircularBuffer::resize(int new_size, const value_type &item) {
    linearize();
    value_type* tmp = m_buffer;
    int stopIndex = size() > new_size ? new_size : size();
    m_buffer = new value_type[new_size];
    for (size_t i = 0; i < stopIndex; i++) {
        m_buffer[i] = tmp[i];
    }
    delete[] tmp;
    if (new_size > m_capacity) {
        for (size_t i = stopIndex; i < new_size; i++) {
            m_buffer[i] = item;
        }
    }
    m_end = 0;
    m_isEmpty = new_size > 0 ? false : true;
    m_capacity = new_size;
}

CircularBuffer &CircularBuffer::operator=(const CircularBuffer &cb) {
    delete[] m_buffer;

    m_capacity = cb.m_capacity;
    m_buffer = new value_type[m_capacity];

    std::copy(cb.m_buffer, cb.m_buffer + m_capacity, m_buffer);

    m_start = cb.m_start;
    m_end = cb.m_end;

    m_isEmpty = cb.m_isEmpty;

    return *this;
}

void CircularBuffer::swap(CircularBuffer &cb) {
    std::swap(m_buffer, cb.m_buffer);
    std::swap(m_capacity, cb.m_capacity);
    std::swap(m_start, cb.m_start);
    std::swap(m_end, cb.m_end);
    std::swap(m_isEmpty, cb.m_isEmpty);
}

void CircularBuffer::push_back(const value_type &item) {
    m_buffer[m_end] = item;
    if (full()) {
        m_end = mod(m_end + 1, m_capacity);
        m_start = mod(m_start + 1, m_capacity);
    } else {
        m_end = mod(m_end + 1, m_capacity);
    }

    if (m_isEmpty) {
        m_isEmpty = false;
    }
}

void CircularBuffer::push_front(const value_type &item) {
    if (full()) {
        m_end = mod(m_end - 1, m_capacity);
        m_start = mod(m_start - 1, m_capacity);

    } else {
        m_start = mod(m_start - 1, m_capacity);
    }
    m_buffer[m_start] = item;
    if (m_isEmpty) {
        m_isEmpty = false;
    }
}

void CircularBuffer::pop_back() {
    if (size() == 1) {
        m_end = 0;
        m_start = 0;
        m_isEmpty = true;
    } else {
        m_end = mod(m_end - 1, m_capacity);
    }
}

void CircularBuffer::pop_front() {
    if (size() == 1) {
        m_end = 0;
        m_start = 0;
        m_isEmpty = true;
    } else {
        m_start = mod(m_start + 1, m_capacity);
    }
}

void CircularBuffer::insert(int pos, const value_type &item) {
    pos = mod(pos, size());
    m_buffer[mod(m_start + pos, m_capacity - 1)] = item;
}

void CircularBuffer::erase(int first, int last) {

    if (first < 0 || last > size())
        throw std::out_of_range("Incorrect index first or last");

    for (int i = last; i < size(); ++i) {
        m_buffer[mod(first + i - last, m_capacity)] =
            m_buffer[mod(i, m_capacity)];
    }

    m_end = mod(m_end - (last - first), m_capacity);
}

void CircularBuffer::clear() {
    m_end = 0;
    m_start = 0;
    m_isEmpty = true;
}

bool operator==(const CircularBuffer &a, const CircularBuffer &b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (size_t i = 0; i < a.size(); i++) {
        if (a[i] != b[i])
            return false;
    }
    return true;
}

bool operator!=(const CircularBuffer &a, const CircularBuffer &b) {
    return !(a == b);
}
