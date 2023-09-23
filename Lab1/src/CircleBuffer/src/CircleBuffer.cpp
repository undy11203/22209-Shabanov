#include <stdexcept>

#include "../includes/CircleBuffer.hpp"

namespace {
int mod(const int &a, const int &b) { return (a % b + b) % b; }
} // namespace

CircularBuffer::CircularBuffer()
    : m_capacity{0}, m_buffer{nullptr}, m_start{}, m_end{0}, m_isEmpty{true} {}

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
    int index = mod(m_start + i, m_capacity - 1);
    return m_buffer[index];
}

const value_type &CircularBuffer::operator[](int i) const {
    int index = mod(m_start + i, m_capacity - 1);
    return m_buffer[index];
}

value_type &CircularBuffer::at(int i) {
    if (i > this->size() - 1 && i < 0)
        throw std::out_of_range("Array index out of bounds");
    int index = mod(m_start + i, m_capacity - 1);
    return m_buffer[index];
}

const value_type &CircularBuffer::at(int i) const {
    if (i > this->size() - 1 && i < 0)
        throw std::out_of_range("Array index out of bounds");
    int index = mod(m_start + i, m_capacity - 1);
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
    for (int i = 0; i < m_capacity; i++) {
        tmp[i] = this->at(i);
    }
    delete[] m_buffer;
    m_buffer = tmp;
    m_end = mod(this->size(), m_capacity);
    m_start = 0;
    return m_buffer;
}

bool CircularBuffer::is_linearized() const {
    if (m_start == 0) {
        return true;
    }
    return false;
}

void CircularBuffer::rotate(int new_begin) {
    new_begin = mod(new_begin, m_capacity);
    int interval = this->size() - new_begin;
    int next = new_begin + interval > mod(m_end - 1, m_capacity)
                   ? mod(new_begin + interval + (m_capacity - this->size()),
                         m_capacity)
                   : mod(new_begin + interval, m_capacity);
    value_type tmp = m_buffer[new_begin];
    for (int i = 0; i < this->size(); i++) {
        std::swap(tmp, m_buffer[next]);
        next =
            next + interval > mod(m_end - 1, m_capacity)
                ? mod(next + interval + (m_capacity - this->size()), m_capacity)
                : mod(next + interval, m_capacity);
    }
}

int CircularBuffer::size() const {
    if (m_isEmpty) {
        return 0;
    }
    int lastIndex = mod(m_end - 1, m_capacity);

    int size = lastIndex >= m_start ? lastIndex - m_start + 1
                                    : m_capacity - (m_start - lastIndex) + 1;
    return size;
}

bool CircularBuffer::empty() const {
    return size() == 0;
        return true;
    }
    return false;
}

bool CircularBuffer::full() const {
    return size() == capacity();
        return true;
    }
    return false;
}

int CircularBuffer::reserve() const { return m_capacity - this->size(); }

int CircularBuffer::capacity() const { return m_capacity; }

void CircularBuffer::set_capacity(int new_capacity) {
    this->linearize();
    value_type *tmp = new value_type[new_capacity];

    if (new_capacity < m_capacity) {
        m_end = 0;
        for (size_t i = 0; i < new_capacity; i++) {
            tmp[i] = m_buffer[i];
        }
    } else {
        m_end = mod(m_end - 1, m_capacity) + 1;
        for (size_t i = 0; i < m_capacity; i++) {
            tmp[i] = m_buffer[i];
        }
    }
    m_capacity = new_capacity;
    delete[] m_buffer;
    m_buffer = tmp;
}

void CircularBuffer::resize(int new_size, const value_type &item) {
    this->linearize();
    value_type *tmp = m_buffer;
    m_buffer = new value_type[new_size];
    for (size_t i = 0; i < this->size(); i++) {
        m_buffer[i] = tmp[i];
    }
    delete[] tmp;

    if (new_size > m_capacity) {
        for (size_t i = m_capacity - 1; i < new_size; i++) {
            m_buffer[i] = item;
        }
    }
    m_end = 0;

    m_capacity = new_size;
}

CircularBuffer &CircularBuffer::operator=(const CircularBuffer &cb) {
    if (m_buffer) {
        delete[] m_buffer;
    }

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
    if (this->full()) {
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
    if (this->full()) {
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
    if (this->size() == 1) {
        m_end = 0;
        m_start = 0;
        m_isEmpty = true;
    } else {
        m_end = mod(m_end - 1, m_capacity);
    }
}

void CircularBuffer::pop_front() {
    if (this->size() == 1) {
        m_end = 0;
        m_start = 0;
        m_isEmpty = true;
    } else {
        m_start = mod(m_start + 1, m_capacity);
    }
}

void CircularBuffer::insert(int pos, const value_type &item) {
    pos = mod(pos, this->size());
    m_buffer[mod(m_start + pos, m_capacity - 1)] = item;
}

void CircularBuffer::erase(int first, int last) {

    if (first < 0 || last > this->size())
        throw std::out_of_range("Incorrect index first or last");

    for (int i = last; i < this->size(); ++i) {
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
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const CircularBuffer &a, const CircularBuffer &b) {
    return !(a == b);
}
