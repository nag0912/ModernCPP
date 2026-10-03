// nullptr — real-time example
// Compile: g++ -std=c++11 -O2 -Wall example.cpp -o example

#include <iostream>
#include <cstddef> // NULL

void f(int x)   { std::cout << "f(int) called with " << x << "\n"; }
void f(char* p) { std::cout << "f(char*) called, p is " << (void*)p << "\n"; }

template <typename T>
void whatType(T) {
    std::cout << "Deduced type is: " << typeid(T).name() << "\n";
}

int main() {
    // The classic ambiguity NULL/0 cause (commented to avoid real ambiguity error,
    // shown conceptually):
    // f(NULL);   // On many platforms NULL==0 -> resolves to f(int), NOT f(char*)!

    f(nullptr);   // Unambiguously resolves to f(char*)

    // Template deduction difference
    whatType(NULL);     // deduces as an integer type (platform-dependent: int or long)
    whatType(nullptr);  // deduces as std::nullptr_t -- correctly represents "a null pointer"

    // nullptr converts to any pointer type and to bool
    int* ip = nullptr;
    double* dp = nullptr;
    if (!ip) std::cout << "ip is null (nullptr converts to bool)\n";
    if (ip == nullptr) std::cout << "ip == nullptr works as expected\n";

    (void)dp;
    return 0;
}
