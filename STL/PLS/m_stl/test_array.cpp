#include <iostream>
#include "array.hpp"


int main() {
    Array<int, 32> b;
    for (size_t i = 0; i < b.size(); ++i) {
        b[i] = 2;
    }
    for (size_t i = 0; i < b.size(); ++i) {
        std::cout << b[i] << " ";
    }
    std::cout << "\n";
    for (auto it = b.begin(); it != b.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    auto a = Array{2, 1, 0};
    for (size_t i = 0; i < a.size(); ++i) {
        std::cout << a[i] << " ";
    }
    return 0;
}