#include <iostream>
#include <set>
#include "printer.h"

struct MyComp {
    bool operator()(std::string const &a, std::string const &b) const {
        return a[0] < b[0];
    }
};

int main() {

    // vector 连续 无序 可重 随机访问位置 "动态数组"
    // set 非连续 有序 不可重 查找值 "有序集合 红黑树"
    std::set<std::string, MyComp> b = {"arch", "any", "zero", "Linux"};
    std::cout << "set=" << b << std::endl;

    // set 为双向迭代器 * != == ++ --
    // vector 为随机访问迭代器 * != == ++ -- + - += -= []



    return 0;
}