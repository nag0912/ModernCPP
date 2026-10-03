// enum class — real-time example
// Compile: g++ -std=c++11 -O2 -Wall example.cpp -o example

#include <iostream>
#include <cstdint>

// Two enums with colliding enumerator names -- fine because they're scoped
enum class Color { Red, Green, Blue };
enum class TrafficLight { Red, Yellow, Green };

// Fixed underlying type -- useful for network/serialization code
enum class StatusCode : std::uint8_t { Ok = 0, Error = 1, Pending = 2 };

std::ostream& operator<<(std::ostream& os, Color c) {
    switch (c) {
        case Color::Red:   return os << "Red";
        case Color::Green: return os << "Green";
        case Color::Blue:  return os << "Blue";
    }
    return os;
}

int main() {
    Color c = Color::Red;
    TrafficLight t = TrafficLight::Red; // no clash with Color::Red

    std::cout << "Color: " << c << "\n";

    // Must explicitly cast to get the integer value -- prevents silent bugs
    int asInt = static_cast<int>(c);
    std::cout << "Color::Red as int: " << asInt << "\n";

    (void)t;

    // Underlying type demo
    StatusCode sc = StatusCode::Pending;
    std::cout << "StatusCode::Pending underlying value: "
              << static_cast<int>(sc)
              << " (sizeof = " << sizeof(sc) << " byte)\n";

    return 0;
}
