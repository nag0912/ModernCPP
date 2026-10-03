// constexpr — real-time example
// Compile: g++ -std=c++11 -O2 -Wall example.cpp -o example

#include <iostream>

// C++11 constexpr function: body restricted to a single return statement.
// Recursion stands in for loops, which weren't allowed yet.
constexpr int factorial(int n) {
    return n <= 1 ? 1 : n * factorial(n - 1);
}

constexpr int square(int x) {
    return x * x;
}

int main() {
    // Computed at COMPILE time -- verify by using it as an array bound
    constexpr int fact5 = factorial(5);
    static_assert(fact5 == 120, "factorial(5) should be 120");
    std::cout << "factorial(5) = " << fact5 << " (computed at compile time)\n";

    int arr[square(4)]; // square(4)=16 must be a compile-time constant to size an array
    std::cout << "Array sized by constexpr square(4): " << sizeof(arr) / sizeof(int) << " ints\n";

    // constexpr function called with a RUNTIME value -- just runs normally
    int userInput;
    std::cout << "Enter a number (try 6): ";
    std::cin >> userInput;
    int runtimeResult = factorial(userInput); // evaluated at runtime, perfectly legal
    std::cout << "factorial(" << userInput << ") = " << runtimeResult << " (computed at runtime)\n";

    // const vs constexpr
    const int c1 = userInput;       // fine, but c1 is NOT usable as a compile-time constant
    constexpr int c2 = 42;          // must be a constant expression
    // int badArr[c1];               // ERROR: c1 isn't known at compile time
    int goodArr[c2];                // fine
    (void)c1; (void)goodArr;

    return 0;
}
