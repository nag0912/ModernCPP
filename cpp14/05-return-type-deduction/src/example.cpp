// Function return type deduction & decltype(auto) — real-time example
// Compile: g++ -std=c++14 -O2 -Wall example.cpp -o example

#include <iostream>
#include <string>

// C++14: return type deduced purely from the return statement, no trailing -> needed
template <typename T, typename U>
auto add(T t, U u) {
    return t + u;
}

auto getValue() { return 42; } // deduces int

// --- The auto-strips-references trap ---
std::string globalName = "Alice";
const std::string& getNameRef() { return globalName; }

auto getName_auto() { return getNameRef(); }           // returns std::string BY VALUE (a copy!)
decltype(auto) getName_decltype() { return getNameRef(); } // returns const std::string& (preserved)

int main() {
    std::cout << "add(2, 3) = " << add(2, 3) << "\n";
    std::cout << "add(1.5, 2) = " << add(1.5, 2) << "\n";
    std::cout << "getValue() = " << getValue() << "\n";

    std::cout << "\n--- auto strips reference-ness on return; decltype(auto) preserves it ---\n";

    auto copy = getName_auto();           // a genuine copy of globalName
    const auto& ref = getName_decltype(); // a real reference to globalName (no copy)

    std::cout << "Before modifying globalName: copy=" << copy << " ref=" << ref << "\n";
    globalName = "Bob";
    std::cout << "After modifying globalName:  copy=" << copy
              << " (unchanged, it was a copy)   ref=" << ref
              << " (changed! it's a real reference)\n";

    return 0;
}
