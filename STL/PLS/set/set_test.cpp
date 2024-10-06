#include <iostream>
#include <set>
#include <unordered_set>
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
    std::cout << "set=" << b << "\n";

    // set 为双向迭代器 * != == ++ --
    // vector 为随机访问迭代器 * != == ++ -- + - += -= []
    // set 可以使用 next+  advance+=
    // distance指针之间的元素个数  prev-

    std::set<int> a = {1, 32, 4, 1, 64};
    std::cout << "set=" << a << "\n";

    // ----------------------------------
    auto result1 = a.insert(3); // 增
    std::cout << result1.second << "\n";

    auto result2 = a.insert(4);
    std::cout << result2.second << "\n";

    // ----------------------------------
    auto it = a.find(32); // 查
    std::cout << *it << "\n";
    // std::cout << *std::prev(it) << "\n";
    // std::cout << *std::next(it) << "\n";

    // if (a.find(3) != a.end()) ...
    // if (a.count(3)) ...

    // lower_bound >=x
    // upper_bound >x

    // ----------------------------------
    a.erase(4); // 删
    std::cout << a << "\n";
    a.erase(a.begin());
    std::cout << a << "\n";
    a.erase(std::prev(a.end()));
    std::cout << a << "\n";
    // a.erase(a.find(1), a.find(64)) 这样不安全
    // a.erase(a.lower_bound(x), a.upper_bound(y));

    // ----------------------------------
    // 改???
    // 不能直接改 先删除再插入

    for (auto it = a.begin(); it != a.end(); ++it) {
        int value = *it;
        std::cout << value << "\n";
    }
    for (auto value : a) { // 与上一版本完全等价 不如直接写完整版
        std::cout << value << "\n";
    }
    // std::cout << *(--a.end()) << "\n";

    std::vector<int> c(a.begin(), a.end());
    std::cout << c << "\n";

    a.clear();
    // a = {};
    // a.erase(a.begin(), a.end());

    // multiset 可重复
    // equal_range() => [lower_bound(), upper_bound()]
    std::multiset<int> d = {1, 1, 2, 2, 3};
    auto r = d.equal_range(2);
    size_t n = std::distance(r.first, r.second); // 直接count()也行
    std::cout << n << "\n";
    // find 会找到第一个位置


    // unordered_set 哈希表
    std::unordered_set<int> e = {1, 4, 2, 8, 5, 8};

    std::cout << e << "\n";

    return 0;
}