// static_assert — real-time example
// Compile: g++ -std=c++11 -O2 -Wall example.cpp -o example

#include <iostream>
#include <type_traits>
#include <cstdint>
#include <cassert>

// 1) Validating template parameters at compile time
template <typename T>
T add(T a, T b) {
    static_assert(std::is_arithmetic<T>::value, "add() requires an arithmetic type");
    return a + b;
}

// 2) Sanity-checking struct layout/size assumptions (e.g. for a wire protocol)
#pragma pack(push, 1)
struct NetworkPacket {
    uint32_t header;
    uint8_t  payload[12];
};
#pragma pack(pop)
static_assert(sizeof(NetworkPacket) == 16, "NetworkPacket must be exactly 16 bytes for wire format");

// 3) Platform assumption check
static_assert(sizeof(void*) == 8, "This code assumes a 64-bit platform");

int main() {
    std::cout << "add(3, 4) = " << add(3, 4) << "\n";
    std::cout << "add(1.5, 2.5) = " << add(1.5, 2.5) << "\n";

    // add(std::string("a"), std::string("b")); // ERROR if uncommented:
    // static_assert fails at compile time: "add() requires an arithmetic type"

    std::cout << "sizeof(NetworkPacket) = " << sizeof(NetworkPacket) << " bytes (verified at compile time)\n";

    // --- static_assert vs runtime assert comparison ---
    int x = 5;
    assert(x == 5); // RUNTIME check -- would abort the program if false, costs a branch
    std::cout << "runtime assert(x==5) passed (checked while the program was running)\n";

    // static_assert(x == 5, "..."); // ERROR if uncommented: x is not a compile-time constant!
    // static_assert only works on genuine compile-time constant expressions.

    constexpr int y = 5;
    static_assert(y == 5, "y must be 5"); // fine -- y IS a compile-time constant
    std::cout << "static_assert(y==5) checked at COMPILE time, zero runtime cost\n";

    return 0;
}
