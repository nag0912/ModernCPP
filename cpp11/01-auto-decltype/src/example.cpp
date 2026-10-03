// auto & decltype — real-time example
// Compile: g++ -std=c++11 -O2 -Wall example.cpp -o example

#include <iostream>
#include <vector>
#include <map>
#include <string>

// Trailing return type: needed in C++11 because the return type
// depends on parameters not yet in scope at the point the return
// type would normally be written.
template <typename T, typename U>
auto add(T t, U u) -> decltype(t + u) {
    return t + u;
}

int main() {
    // --- auto: deduces type from initializer ---
    auto i = 42;            // int
    auto d = 3.14;          // double
    auto s = std::string("hello"); // std::string

    std::cout << "i=" << i << " d=" << d << " s=" << s << "\n";

    // --- Without auto, this is painful ---
    std::map<std::string, std::vector<int>> scores;
    scores["alice"] = {90, 85, 88};
    scores["bob"]   = {70, 75};

    // Old way: std::map<std::string, std::vector<int>>::iterator it = scores.begin();
    for (auto it = scores.begin(); it != scores.end(); ++it) {
        std::cout << it->first << ": ";
        for (auto score : it->second) std::cout << score << " ";
        std::cout << "\n";
    }

    // --- auto strips const/reference; demonstrate the trap ---
    std::vector<int> nums = {1, 2, 3};
    for (auto x : nums) x *= 2;       // copy — nums unchanged
    std::cout << "After copy-loop (unchanged): ";
    for (auto x : nums) std::cout << x << " ";
    std::cout << "\n";

    for (auto& x : nums) x *= 2;      // reference — nums actually modified
    std::cout << "After reference-loop (doubled): ";
    for (auto x : nums) std::cout << x << " ";
    std::cout << "\n";

    // --- decltype: exact type, preserves references ---
    int x = 10;
    int& rx = x;
    decltype(rx) y = x;   // y is int& — an alias for x
    y = 99;
    std::cout << "x after modifying y (decltype(rx) is int&): " << x << "\n";

    // Parens matter! decltype((x)) is int&, not int
    decltype((x)) z = x;  // int&
    z = 123;
    std::cout << "x after modifying z (decltype((x)) is int&): " << x << "\n";

    // --- trailing return type with decltype ---
    std::cout << "add(2, 3.5) = " << add(2, 3.5) << "\n";

    return 0;
}
