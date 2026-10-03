// std::tuple & std::tie — real-time example
// Compile: g++ -std=c++11 -O2 -Wall example.cpp -o example

#include <iostream>
#include <tuple>
#include <string>
#include <vector>
#include <algorithm>

// Real-world pattern: a function returning multiple heterogeneous values
std::tuple<bool, std::string, int> parseUser(const std::string& input) {
    if (input.empty()) return std::make_tuple(false, "", 0);
    return std::make_tuple(true, input, static_cast<int>(input.size()));
}

int main() {
    std::cout << "--- Basic tuple creation & access ---\n";
    std::tuple<int, std::string, double> t(1, "hello", 3.14);
    std::cout << "get<0>=" << std::get<0>(t)
              << " get<1>=" << std::get<1>(t)
              << " get<2>=" << std::get<2>(t) << "\n";

    std::get<0>(t) = 99; // get<> returns a reference -- modifiable
    std::cout << "after modifying get<0>: " << std::get<0>(t) << "\n";

    std::cout << "\n--- make_tuple (type deduction) ---\n";
    auto t2 = std::make_tuple(42, std::string("world"), 2.71);
    std::cout << "t2: " << std::get<0>(t2) << ", " << std::get<1>(t2) << ", " << std::get<2>(t2) << "\n";

    std::cout << "\n--- std::tie: unpacking into existing variables ---\n";
    bool ok; std::string name; int len;
    std::tie(ok, name, len) = parseUser("Alice");
    std::cout << "ok=" << std::boolalpha << ok << " name=" << name << " len=" << len << "\n";

    // std::ignore to skip fields
    std::tie(ok, std::ignore, len) = parseUser("Bob123");
    std::cout << "ok=" << ok << " len=" << len << " (name ignored)\n";

    std::cout << "\n--- tuple lexicographic comparison: sort by multiple keys ---\n";
    std::vector<std::tuple<int, int>> points = {{3, 1}, {1, 5}, {1, 2}, {2, 0}};
    std::sort(points.begin(), points.end()); // sorts by first element, ties broken by second
    for (auto& p : points) {
        std::cout << "(" << std::get<0>(p) << "," << std::get<1>(p) << ") ";
    }
    std::cout << "\n";

    return 0;
}
