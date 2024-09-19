#include <iostream>


int main() {
    std::cout << "Hello\n";
    int &&a = (int)10;
    const int &b = a;
    std::cout << b;
    return 0;
}