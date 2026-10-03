// Relaxed constexpr — real-time example
// Compile: g++ -std=c++14 -O2 -Wall example.cpp -o example

#include <iostream>

// C++11 style: forced into recursion (single-expression body)
constexpr int factorial11(int n) {
    return n <= 1 ? 1 : n * factorial11(n - 1);
}

// C++14 style: ordinary imperative code -- loops, locals, mutation all allowed
constexpr int factorial14(int n) {
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// Another C++14 constexpr example: branching + loop + local state
constexpr bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

constexpr int countPrimesUpTo(int limit) {
    int count = 0;
    for (int i = 2; i <= limit; ++i) {
        if (isPrime(i)) ++count;
    }
    return count;
}

int main() {
    // Both computed at COMPILE time -- verified via static_assert
    constexpr int a = factorial11(5);
    constexpr int b = factorial14(5);
    static_assert(a == 120, "factorial11(5) should be 120");
    static_assert(b == 120, "factorial14(5) should be 120");
    std::cout << "factorial11(5) = " << a << " (C++11-style recursion)\n";
    std::cout << "factorial14(5) = " << b << " (C++14-style loop)\n";

    constexpr int primeCount = countPrimesUpTo(50);
    static_assert(primeCount == 15, "there are 15 primes <= 50");
    std::cout << "Primes up to 50: " << primeCount << " (computed entirely at compile time)\n";

    // Can also run at runtime with a non-constant argument, exactly like C++11
    int n;
    std::cout << "Enter n for factorial14 (try 7): ";
    std::cin >> n;
    std::cout << "factorial14(" << n << ") = " << factorial14(n) << " (computed at runtime)\n";

    return 0;
}
