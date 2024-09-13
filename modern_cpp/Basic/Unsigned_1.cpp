#include <iostream>

int main() {
    std::string s = "Hello World!";
    if (s.find("t") > 0) {
        std::cout << "Found\n";
    } else {
        std::cout << "Not Found\n";
    }
    return 0;
} // why always Found???