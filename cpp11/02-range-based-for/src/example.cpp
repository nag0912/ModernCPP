// Range-based for — real-time example
// Compile: g++ -std=c++11 -O2 -Wall example.cpp -o example

#include <iostream>
#include <vector>
#include <string>

// Custom iterable type: a simple range [start, end)
class IntRange {
    int start_, end_;
public:
    IntRange(int start, int end) : start_(start), end_(end) {}

    class iterator {
        int val;
    public:
        iterator(int v) : val(v) {}
        int operator*() const { return val; }
        iterator& operator++() { ++val; return *this; }
        bool operator!=(const iterator& o) const { return val != o.val; }
    };

    iterator begin() const { return iterator(start_); }
    iterator end()   const { return iterator(end_); }
};

int main() {
    std::vector<std::string> names = {"Alice", "Bob", "Carol"};

    // 1) Copy iteration (safe, wasteful for big objects)
    std::cout << "By value: ";
    for (auto n : names) std::cout << n << " ";
    std::cout << "\n";

    // 2) Reference iteration — mutate in place
    for (auto& n : names) n += "!";
    std::cout << "After mutation: ";
    for (const auto& n : names) std::cout << n << " ";  // 3) const ref = no copy, read-only
    std::cout << "\n";

    // 4) Works on raw arrays
    int arr[5] = {10, 20, 30, 40, 50};
    std::cout << "Raw array: ";
    for (auto x : arr) std::cout << x << " ";
    std::cout << "\n";

    // 5) Custom range type — works because it has begin()/end()
    std::cout << "Custom IntRange(1,6): ";
    for (auto x : IntRange(1, 6)) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
