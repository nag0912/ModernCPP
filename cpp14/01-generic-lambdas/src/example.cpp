// Generic lambdas — real-time example
// Compile: g++ -std=c++14 -O2 -Wall example.cpp -o example

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

int main() {
    // A single lambda, usable with ANY type supporting operator+
    auto add = [](auto a, auto b) { return a + b; };

    std::cout << "add(1, 2) = " << add(1, 2) << "\n";
    std::cout << "add(1.5, 2.5) = " << add(1.5, 2.5) << "\n";
    std::cout << "add(string,string) = " << add(std::string("foo"), std::string("bar")) << "\n";

    // The two auto parameters can deduce to DIFFERENT types
    std::cout << "add(1, 2.5) = " << add(1, 2.5) << " (int + double mixed)\n";

    // Real-world use: a generic comparator reused across different vector types
    auto byAbsoluteValue = [](auto a, auto b) { return std::abs(a) < std::abs(b); };

    std::vector<int> ints = {-5, 3, -1, 4, -2};
    std::sort(ints.begin(), ints.end(), byAbsoluteValue);
    std::cout << "ints sorted by |x|: ";
    for (int x : ints) std::cout << x << " ";
    std::cout << "\n";

    std::vector<double> doubles = {-5.5, 3.3, -1.1, 4.4};
    std::sort(doubles.begin(), doubles.end(), byAbsoluteValue); // same lambda, different type!
    std::cout << "doubles sorted by |x|: ";
    for (double x : doubles) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
