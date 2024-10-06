#pragma once
template <class T, size_t N>
struct Array {
    T m_elements[N];
    using value_type = T;
    using iterator = T *;
    using const_iterator = T *;
    T &operator[](size_t i) noexcept {
        return m_elements[i];
    }
    T const &operator[](size_t i) const noexcept {
        return m_elements[i];
    }
    T &at(size_t i) {
        if (i >= N) [[unlikely]]
            throw std::runtime_error("out of range!");
        return m_elements[i];
    }
    T const &at(size_t i) const {
        if (i >= N) [[unlikely]]
            throw std::runtime_error("out of range!");
        return m_elements[i];
    }
    static constexpr size_t size() noexcept {
        return N;
    }
    T const *data() const noexcept {
        return m_elements;
    }
    T *data() noexcept {
        return m_elements;
    }
    T *begin() noexcept {
        return m_elements;
    }
    T *end() noexcept {
        return m_elements + N;
    }
    T const *begin() const noexcept {
        return m_elements;
    }
    T const *end() const noexcept {
        return m_elements + N;
    } // 有了begin 和 end 可以使用for (auto &ai : a) {...}

    // concept RandomAccessorIterator
    // *p
    // p->...
    // ++p
    // --p
    // p += n
    // p -= n
    // p + n
    // p - n
    // p[n]
    // p1 - p2
    // p1 != p2
    // p1 < p2
};
template <class T, class... Ts>
Array(T, Ts...) -> Array<T, 1 + sizeof...(Ts)>;