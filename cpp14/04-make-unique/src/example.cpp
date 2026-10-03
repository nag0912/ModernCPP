// std::make_unique — real-time example
// Compile: g++ -std=c++14 -O2 -Wall example.cpp -o example

#include <iostream>
#include <memory>

struct Widget {
    int id;
    explicit Widget(int i) : id(i) { std::cout << "Widget(" << id << ") created\n"; }
    ~Widget() { std::cout << "Widget(" << id << ") destroyed\n"; }
};

void process(std::unique_ptr<Widget> a, std::unique_ptr<Widget> b) {
    std::cout << "Processing Widget(" << a->id << ") and Widget(" << b->id << ")\n";
}

int main() {
    std::cout << "--- Old (C++11) way: naked new wrapped manually ---\n";
    std::unique_ptr<Widget> p1(new Widget(1)); // works, but has the exception-safety
                                                  // issue described in the README when
                                                  // used as part of a multi-argument call
    std::cout << "p1 created, id=" << p1->id << "\n";

    std::cout << "\n--- C++14 way: make_unique, exception-safe and concise ---\n";
    auto p2 = std::make_unique<Widget>(2); // perfectly forwards 2 to Widget's constructor
    std::cout << "p2 created, id=" << p2->id << "\n";

    std::cout << "\n--- Exception-safe multi-argument call ---\n";
    // Each make_unique call is atomic from an exception-safety standpoint --
    // no window where a raw, newly-allocated Widget* exists without an owner.
    process(std::make_unique<Widget>(3), std::make_unique<Widget>(4));

    std::cout << "\n--- make_unique for arrays (also supported) ---\n";
    auto arr = std::make_unique<int[]>(5); // allocates an array of 5 ints
    for (int i = 0; i < 5; ++i) arr[i] = i * i;
    std::cout << "arr: ";
    for (int i = 0; i < 5; ++i) std::cout << arr[i] << " ";
    std::cout << "\n";

    return 0;
}
