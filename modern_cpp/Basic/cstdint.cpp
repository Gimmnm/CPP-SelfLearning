#include <cstdint>
#include <type_traits>

int main() {
    std::uint16_t a;
    std::is_same_v<std::uint16_t, unsigned short>;
    return 0;
}