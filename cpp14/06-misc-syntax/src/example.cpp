// Misc C++14 syntax — real-time example
// Compile: g++ -std=c++14 -O2 -Wall example.cpp -o example

#include <iostream>

// Variable template -- a templated VALUE, not just a function/class
template <typename T>
constexpr T pi = T(3.1415926535897932385);

[[deprecated("use computeAreaV2() instead")]]
double computeArea(double radius) {
    return pi<double> * radius * radius;
}

double computeAreaV2(double radius) {
    return pi<double> * radius * radius;
}

int main() {
    // Binary literals
    int flags = 0b1010'1100;
    std::cout << "0b1010'1100 = " << flags << " (decimal)\n";

    // Digit separators -- purely cosmetic, compiler ignores the '
    int million = 1'000'000;
    long bigHex = 0xFFFF'FFFFL;
    double piApprox = 3.14159'26535;
    std::cout << "1'000'000 = " << million << "\n";
    std::cout << "0xFFFF'FFFF = " << bigHex << "\n";
    std::cout << "3.14159'26535 = " << piApprox << "\n";

    // Variable templates: same name, different instantiations per type
    std::cout << "pi<float>  = " << pi<float> << "\n";
    std::cout << "pi<double> = " << pi<double> << "\n";

    // [[deprecated]] -- this call will produce a compiler warning, but still runs
    std::cout << "computeArea(2.0) = " << computeArea(2.0) << " (deprecated, see warning above)\n";
    std::cout << "computeAreaV2(2.0) = " << computeAreaV2(2.0) << "\n";

    return 0;
}
