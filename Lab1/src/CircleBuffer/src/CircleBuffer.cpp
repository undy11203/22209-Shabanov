#include <stdexcept>

#include "../includes/CircleBuffer.hpp"

namespace {
template <typename T> T mod(const T &a, const T &b) { return (a % b + b) % b; }
} // namespace

CircularBuffer::CircularBuffer()
    : m_capacity{0}, m_buffer{NULL}, m_start{-1}, m_end{-1} {}

CircularBuffer::CircularBuffer(const CircularBuffer &cb)
    : m_capacity{cb.m_capacity}, m_start{cb.m_start}, m_end{cb.m_end} {
    m_buffer = new value_type[m_capacity];
    for (int i = 0; i < m_capacity; i++) {
        m_buffer[i] = cb.m_buffer[i];
    }
}

CircularBuffer::CircularBuffer(int capacity)
    : m_capacity{capacity}, m_start{0}, m_end{-1} {
    m_buffer = new value_type[capacity];
}

CircularBuffer::CircularBuffer(int capacity, const value_type &elem)
    : m_capacity{capacity}, m_start{0}, m_end{capacity - 1} {
    m_buffer = new value_type[capacity];

    for (size_t i = 0; i < m_capacity; i++) {
        m_buffer[i] = elem;
    }
}

CircularBuffer::~CircularBuffer() { delete[] m_buffer; }

value_type &CircularBuffer::operator[](int i) {
    return const_cast<value_type &>(
        static_cast<const CircularBuffer *>(this)->operator[](i));
}

const value_type &CircularBuffer::operator[](int i) const {
    int index = mod<int>(m_start + i, m_capacity - 1);
    return m_buffer[index];
}

value_type &CircularBuffer::at(int i) {
    return const_cast<value_type &>(
        static_cast<const CircularBuffer *>(this)->at(i));
}

const value_type &CircularBuffer::at(int i) const {
    if (i > m_capacity)
        throw std::out_of_range("Array index out of bounds");
    return m_buffer[i];
}

value_type &CircularBuffer::front() {
    return const_cast<value_type &>(
        static_cast<const CircularBuffer *>(this)->front());
} // Ссылка на первый элемент.

const value_type &CircularBuffer::front() const { return m_buffer[m_start]; }

value_type &CircularBuffer::back() {
    return const_cast<value_type &>(
        static_cast<const CircularBuffer *>(this)->back());
} // Ссылка на последний элемент.

const value_type &CircularBuffer::back() const { return m_buffer[m_end]; }

value_type *CircularBuffer::linearize() {
    value_type *tmp = new value_type[m_capacity];
    for (int i = 0; i < m_capacity; i++) {
        tmp[i] = this->at(i);
    }
    delete[] m_buffer;
    m_buffer = tmp;
    m_end = this->size() - 1;
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
    if (new_begin > this->size() - 1) {
        throw new std::out_of_range("index out of range");
    }
    int interval = this->size() - new_begin;
    int next =
        new_begin + interval > m_end
            ? mod<int>(new_begin + interval + (m_capacity - this->size()),
                       m_capacity)
            : mod<int>(new_begin + interval, m_capacity);
    ;
    value_type tmp = m_buffer[new_begin];
    for (int i = 0; i < this->size(); i++) {
        std::swap(tmp, m_buffer[next]);
        next = next + interval > m_end
                   ? mod<int>(next + interval + (m_capacity - this->size()),
                              m_capacity)
                   : mod<int>(next + interval, m_capacity);
    }
}

int CircularBuffer::size() const {
    if (m_end == -1) {
        return 0;
    }

    int size = m_end >= m_start ? m_end - m_start + 1
                                : m_capacity - (m_start - m_end) + 1;
    return size;
}

bool CircularBuffer::empty() const {
    if (this->size() == 0) {
        return true;
    }
    return false;
}

bool CircularBuffer::full() const {
    if (this->size() == this->capacity()) {
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
        m_end = new_capacity - 1;
        for (size_t i = 0; i < new_capacity; i++) {
            tmp[i] = m_buffer[i];
        }

    } else {
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
    m_buffer = (value_type *)realloc(m_buffer, sizeof(value_type) * new_size);
    if (new_size > m_capacity) {
        for (size_t i = m_capacity - 1; i < new_size; i++) {
            m_buffer[i] = item;
        }
    }
    m_end = new_size - 1;

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

    return *this;
}

void CircularBuffer::swap(CircularBuffer &cb) {
    std::swap(m_buffer, cb.m_buffer);
    std::swap(m_capacity, cb.m_capacity);
    std::swap(m_start, cb.m_start);
    std::swap(m_end, cb.m_end);
}

void CircularBuffer::push_back(const value_type &item) {

    if (this->full()) {
        m_end = mod<int>(m_end + 1, m_capacity - 1);
        m_start = mod<int>(m_start + 1, m_capacity - 1);
    } else {
        m_end = mod<int>(m_end + 1, m_capacity - 1);
    }
    m_buffer[m_end] = item;
}

void CircularBuffer::push_front(const value_type &item) {

    if (this->full()) {
        m_end = mod<int>(m_end - 1, m_capacity - 1);
        m_start = mod<int>(m_start - 1, m_capacity - 1);

    } else {
        m_start = mod<int>(m_start - 1, m_capacity - 1);
    }
    m_buffer[m_start] = item;
}

void CircularBuffer::pop_back() {
    if (this->size() == 1) {
        m_end = -1;
        m_start = 0;
    } else {
        m_end = mod<int>(m_end - 1, m_capacity - 1);
    }
}

void CircularBuffer::pop_front() {
    if (this->size() == 1) {
        m_end = -1;
        m_start = 0;
    } else {
        m_start = mod<int>(m_start + 1, m_capacity - 1);
    }
}

void CircularBuffer::insert(
    int pos, const value_type &item) { // нужна доработка, чтобы обработать
    if (pos > this->capacity())
        throw std::logic_error("Cannot be inserted into such a position");
    m_buffer[mod<int>(m_start + pos, m_capacity - 1)] = item;
}

void CircularBuffer::erase(int first, int last) {
    if (first != 0 && last != this->size() - 1)
        throw std::logic_error("Can't delete the middle");
    if (first == 0 && last == this->size() - 1) {
        m_start = 0;
        m_end = -1;
    } else if (first == 0) {
        m_start = mod<int>(m_start + (last - first), m_capacity - 1);
    } else if (last == this->size() - 1) {
        m_end = mod<int>(m_end - (last - first), m_capacity - 1);
    }
}

void CircularBuffer::clear() {
    m_end = -1;
    m_start = 0;
}

bool operator==(const CircularBuffer &a, const CircularBuffer &b) {
    if (a.size() != b.size()) {
        return false;
    }
    if (a.capacity() != b.capacity()) {
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
