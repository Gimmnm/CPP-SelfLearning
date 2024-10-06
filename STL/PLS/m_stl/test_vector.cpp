#include <iostream>
#include <vector>
#include "vector.hpp"

int main() {
    Vector<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.print();
    arr.assign(5, 42);
    arr.print();
    arr.insert(arr.begin() + 2, 3, 32);
    arr.print();
    Vector<int> b = {1, 32, 22};
    b.print();
    b.insert(b.end(), {1, 42, 2});
    b.print();
    return 0;
}