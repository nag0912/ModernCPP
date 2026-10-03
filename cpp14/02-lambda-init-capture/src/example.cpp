// Lambda init-capture — real-time example
// Compile: g++ -std=c++14 -O2 -Wall example.cpp -o example

#include <iostream>
#include <memory>
#include <functional>

struct Widget {
    int id;
    explicit Widget(int i) : id(i) { std::cout << "Widget(" << id << ") created\n"; }
    ~Widget() { std::cout << "Widget(" << id << ") destroyed\n"; }
    void greet() const { std::cout << "Widget(" << id << ") says hi\n"; }
};

int main() {
    std::cout << "--- Moving a unique_ptr INTO a lambda's closure ---\n";
    std::unique_ptr<Widget> p = std::make_unique<Widget>(1);

    // C++11 would be unable to capture p by value (unique_ptr isn't copyable).
    // Init-capture moves it directly into the closure's own storage.
    auto callback = [owned = std::move(p)]() {
        owned->greet();
    };

    std::cout << "p (outer) is now: " << (p ? "non-null" : "null (moved away)") << "\n";
    callback(); // the lambda now exclusively owns the Widget
    callback(); // can call multiple times, closure keeps ownership

    std::cout << "\n--- Capturing a COMPUTED expression, not just a variable ---\n";
    int x = 10;
    auto doubled = [y = x * 2]() { return y; };
    x = 999; // changing x afterward has no effect -- y was computed at creation time
    std::cout << "doubled() = " << doubled() << " (captured x*2 at creation, x later changed to 999)\n";

    std::cout << "\n--- Move-capturing lambdas and std::function: a gotcha ---\n";
    auto moveOnlyLambda = [w = std::make_unique<Widget>(2)]() {
        w->greet();
    };
    // A lambda that move-captures a unique_ptr is itself NON-copyable (its closure
    // type's copy ctor is implicitly deleted, since unique_ptr can't be copied).
    // std::function REQUIRES its target to be copy-constructible, so this would fail:
    //   std::function<void()> stored = moveOnlyLambda; // ERROR: static assertion failed
    // Call it directly instead, or use std::move_only_function (C++23) if you need
    // a type-erased wrapper around a move-only callable.
    moveOnlyLambda();

    std::cout << "\n--- end of main (destructors fire here) ---\n";
    return 0;
}
