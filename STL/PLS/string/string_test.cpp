#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

int main() {

    std::cout << std::string("hel\0lo", 6) << std::endl;

    auto s = (std::stringstream() << std::setprecision(4) << 3.1415f).str();
    std::cout << s << std::endl;

    // at [] 同vector
    // s.size()
    // substr(size_t pos = 0, size_t len = -1);
    // find 各种重载 rfind find_first_of find_first_not_of
    // replace
    // append  += 也有 capacity的概念
    // insert
    // erase 

    // string_view 类似引用 而string是和具体字符串的强绑定
    // 胖指针思想

    return 0;
}