// Lambdas — real-time example
// Compile: g++ -std=c++11 -O2 -Wall example.cpp -o example

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main() {
    std::vector<int> v = {5, 3, 8, 1, 9, 2};

    // Inline lambda passed directly to an algorithm
    std::sort(v.begin(), v.end(), [](int a, int b) { return a < b; });
    std::cout << "Sorted: ";
    for (int x : v) std::cout << x << " ";
    std::cout << "\n";

    int countEven = std::count_if(v.begin(), v.end(),
                                   [](int x) { return x % 2 == 0; });
    std::cout << "Even count: " << countEven << "\n";

    // --- Capture by value vs by reference ---
    int threshold = 5;

    auto byValue = [threshold](int x) { return x > threshold; };
    threshold = 100; // change AFTER lambda created
    std::cout << "byValue still uses threshold=5 snapshot: "
              << std::boolalpha << byValue(6) << "\n"; // true, since 6 > 5 (frozen copy)

    threshold = 5; // reset
    auto byRef = [&threshold](int x) { return x > threshold; };
    threshold = 100; // change BEFORE calling
    std::cout << "byRef sees live threshold=100: "
              << byRef(6) << "\n"; // false, since 6 is not > 100 (live reference)

    // --- mutable: modify a captured-by-value variable inside the lambda ---
    int counter = 0;
    auto incrementer = [counter]() mutable {
        counter++;
        return counter;
    };
    std::cout << "incrementer() calls: "
              << incrementer() << " " << incrementer() << " " << incrementer()
              << " (lambda's own copy increments; outer counter unaffected: " << counter << ")\n";

    // --- storing lambdas: auto vs std::function ---
    auto exactType = [](int x) { return x * 2; };          // zero-overhead closure type
    std::function<int(int)> typeErased = exactType;         // type-erased wrapper

    std::vector<std::function<int(int)>> callbacks;
    callbacks.push_back([](int x) { return x + 1; });
    callbacks.push_back([](int x) { return x * x; });
    for (auto& cb : callbacks) std::cout << "callback(4) = " << cb(4) << "\n";

    std::cout << "typeErased(10) = " << typeErased(10) << "\n";

    return 0;
}
