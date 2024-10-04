#include <iostream>

#include <vector>

namespace std {
template <class T>
ostream &operator<<(ostream &os, vector<T> const &v) {
    os << '{';
    auto it = v.begin();
    if (it != v.end()) {
        os << *it;
        for (++it; it != v.end(); ++it) {
            os << ',' << *it;
        }
    }
    os << '}';
    return os;
}
} // namespace std

void print(char const *a, size_t n) {
    for (int i = 0; i < n; i++) {
        std::cout << a[i] << "\n";
    }
}

void print(char const *begptr, char const *endptr) {
    for (char const *ptr = begptr; ptr != endptr; ptr++) {
        char value = *ptr;
        std::cout << value << "\n";
    }
}

template<class Ptr>
void print(Ptr begptr, Ptr endptr) {
    for (Ptr ptr = begptr; ptr != endptr; ptr++) {
        auto value = *ptr;
        std::cout << value << "\n";
    }
}

int main() {
    std::vector<int> a(4);
    std::vector<int> b(4, 233);
    std::vector<int> c{4};
    std::vector<int> d{3, 23, 233, 3};
    std::vector<int> e(std::begin(d), std::end(d));
    std::cout
        << a << "\n"
        << b << "\n"
        << c << "\n"
        << d << "\n";
    b.resize(10, 444);
    std::cout << b << "\n";
    c.clear();
    std::cout << c << "\n";
    d.push_back(12);
    std::cout << d << "\n";
    d.pop_back();
    std::cout << d << "\n";

    std::cout << a.capacity() << "\n";
    a.resize(5);
    std::cout << a.capacity() << "\n";
    a.resize(4);
    a.shrink_to_fit();
    std::cout << a.capacity() << "\n";
    a.push_back(4);
    std::cout << a.capacity() << "\n";

    // a.data();
    // a.capacity();
    // resize(n) 会自动扩容到 max(n, capacity * 2)(push_back同理) 可能移动位置
    // a.reserve(); 预留容量 可能移动位置
    // a.shrink_to_fit(); 释放多余容量 可能移动位置

    std::vector<char> ac = {'h', 'j', 'k', 'l'};
    print(ac.data() + 1, ac.size() - 2);
    print(ac.data(), ac.data() + ac.size());

    // 尽量用 ++p !!!

    // 没有高效的前端插入方法，不如用deque 但是deque内存不连续，也有取舍
    // a.insert(a.begin() + 3, 233); 在指针的位置开始，也就是会插入到第三个位置
    // a.insert(a.begin(), 4, 233);
    // a.insert(a.begin(), {323, 232, 2, 23});
    // a.insert(a.begin(), b.begin(), b.end()); b可以是其他容器
    int aa[] = {323, 2323, 23, 23};
    a.insert(a.end(), std::begin(aa), std::end(aa));
    std::cout << a << "\n";

    // a.assign(b.begin(), end()); 清空原来的所有元素

    // a.erase(a.end());
    // a.erase(a.begin() + 1, a.end());

    return 0;
}