#pragma once
#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <memory>
#include <stdexcept>
#include <utility>

template <class T>
struct Vector {
    T *m_data;
    size_t m_size;
    size_t m_cap;
    Vector() : m_data{nullptr}, m_size{0}, m_cap{0} {}
    
    explicit Vector(size_t n) {
        m_data = new int[n]{};
        m_size = n;
        m_cap = n;
    }

    explicit Vector(size_t n, T val) {
        m_data = new int[n];
        for (size_t i = 0; i < n; i++) {
            m_data[i] = val;
        }
        m_size = n;
        m_cap = n;
    }

    template <std::random_access_iterator InputIt>
    Vector(InputIt first, InputIt last) {
        size_t n = last - first;
        m_data = new int[n];
        m_size = n;
        m_cap = n;
        for (size_t i = 0; i < n; ++i) {
            m_data[i] = *first;
            ++first;
        }
    }

    Vector(std::initializer_list<T> list) : Vector(list.begin(), list.end()) {}

    void resize(size_t n, int val = 0) {
        reserve(n);
        if (n > m_size) {
            for (size_t i = m_size; i < n; ++i) {
                m_data[i] = val;
            }
        }
        m_size = n;
    }

    void reserve(size_t n) {
        if (n <= m_cap) [[likely]]
            return;
        n = std::max(n, m_cap * 2);
        auto old_data = m_data;
        if (n == 0) {
            m_data = nullptr;
            m_cap = 0;
            if (old_data) delete[] old_data;
        } else {
            m_data = new int[n];
            m_cap = n;
            if (old_data) {
                memcpy(m_data, old_data, m_size * sizeof(T));
                delete[] old_data;
            }
        }
    }

    void shirk_to_fit() {
        auto old_data = m_data;
        m_cap = m_size;
        if (m_size == 0) {
            m_data = nullptr;
        } else {
            m_data = new int[m_size];
        }
        if (old_data) {
            if (m_size != 0)
                memcpy(m_data, old_data, m_size * sizeof(T));
            delete[] old_data;
        }
    }

    void clear() {
        resize(0);
    }

    size_t size() const noexcept {
        return m_size;
    }

    size_t capacity() const noexcept {
        return m_cap;
    }

    Vector(Vector const &other) {
        m_size = other.m_size;
        if (m_size != 0) {
            m_data = new int[m_size];
            std::copy(other.m_data, other.m_data + other.m_size, m_data);
        } else {
            m_data = nullptr;
        }
    }

    Vector &operator=(Vector const &other) {
        if (this == &other) {
            return *this;
        }
        reserve(other.m_size);
        m_size = other.m_size;
        for (size_t i = 0; i != m_size; ++i) {
            m_data[i] = other.m_data[i];
        }
        return *this;
    }

    template <std::random_access_iterator InputIt>
    void assign(InputIt first, InputIt last) {
        size_t n = last - first;
        reserve(n);
        m_size = n;
        for (size_t i = 0; i < n; ++i) {
            m_data[i] = *first;
            ++first;
        }
    }

    void assign(size_t n, T val) {
        reserve(n);
        m_size = n;
        for (size_t i = 0; i < n; ++i) {
            m_data[i] = val;
        }
    }
    void assign(std::initializer_list<T> list) {
        assign(list.begin(), list.end());
    }

    Vector(Vector &&other) noexcept : m_size(other.m_size), m_data(other.m_data) {
        other.m_data = nullptr;
        other.m_size = 0;
    }

    Vector &operator=(Vector &&other) noexcept {
        m_data = other.m_data;
        m_size = other.m_size;
        other.m_data = nullptr;
        other.m_size = 0;
        return *this;
    }

    T const &operator[](size_t i) const noexcept {
        return m_data[i];
    }

    T &operator[](size_t i) noexcept {
        return m_data[i];
    }

    T const &at(size_t i) const {
        if (i >= m_size) [[unlikely]]
            throw std::out_of_range("vector::at");
        return m_data[i];
    }

    T &at(size_t i) {
        if (i >= m_size) [[unlikely]]
            throw std::out_of_range("vector::at");
        return m_data[i];
    }

    int const &front() const noexcept {
        return operator[](0);
    }

    T &front() noexcept {
        return operator[](0);
    }

    int const &back() const noexcept {
        return operator[](size() - 1);
    }

    T &back() noexcept {
        return operator[](size() - 1);
    }

    void push_back(T val) {
        reserve(size() + 1);
        m_size = m_size + 1;
        back() = val;
    }

    T *begin() {
        return m_data;
    }

    T *end() {
        return m_data + m_size;
    }

    int const *begin() const {
        return m_data;
    }

    int const *end() const {
        return m_data + m_size;
    }


    void erase(size_t i) {
        for (size_t j = i + 1; j < m_size; ++j) {
            m_data[j - 1] = std::move(m_data[j]);
        }
        resize(m_size - 1);
    }

    void erase(size_t ibeg, size_t iend) {
        size_t diff = iend - ibeg;
        for (size_t j = iend; j < m_size; j++) {
            m_data[j - diff] = std::move(m_data[j]);
        }
        resize(m_size - diff);
    }
    
    void erase(T const *it) {
        size_t i = it - m_data;
        for (size_t j = i + 1; j < m_size; ++j) {
            m_data[j - 1] = std::move(m_data[j]);
        }
        resize(m_size - 1);
    }

    void erase(T const *first, T const *last) {
        size_t ibeg = first - m_data;
        size_t iend = last - m_data;
        size_t diff = iend - ibeg;
        for (size_t j = iend; j < m_size; j++) {
            m_data[j - diff] = std::move(m_data[j]);
        }
        resize(m_size - diff);
    }

    void insert(T const *it, size_t n, T val) {
        size_t j = it - m_data;
        if (n == 0) [[unlikely]]
            return;
        reserve(n + m_size);
        m_size += n;
        for (size_t i = n; i > 0; --i) {
            m_data[j + n + i - 1] = std::move(m_data[j + i - 1]);
        }
        for (size_t i = j; i < j + n; ++i) {
            m_data[i] = val;
        }
    }
    
    template <std::random_access_iterator InputIt>
    void insert(T const *it, InputIt first, InputIt last) {
        size_t n = last - first;
        size_t j = it - m_data;
        if (n == 0) [[unlikely]]
            return;
        reserve(n + m_size);
        m_size += n;
        for (size_t i = n; i > 0; --i) {
            m_data[j + n + i - 1] = std::move(m_data[j + i - 1]);
        }
        for (size_t i = j; i < j + n; ++i) {
            m_data[i] = *first;
            ++first;
        }
    }
    
    void insert(T const *it, std::initializer_list<T> list) {
        insert(it, list.begin(), list.end());
    }

    void print() const noexcept {
        for (size_t i = 0; i < size(); ++i) {
            std::cout << m_data[i] << " ";
        }
        std::cout << "\n";
    }

    ~Vector() {
        delete[] m_data;
    }
};