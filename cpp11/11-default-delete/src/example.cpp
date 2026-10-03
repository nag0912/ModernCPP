// = default & = delete — real-time example
// Compile: g++ -std=c++11 -O2 -Wall example.cpp -o example

#include <iostream>

class Widget {
public:
    Widget() = default;           // explicitly keep the default ctor...
    explicit Widget(int x) : x_(x) {}  // ...even though we also have this one
    int get() const { return x_; }
private:
    int x_ = 0;
};

class NonCopyable {
public:
    NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete;             // compile error if copied
    NonCopyable& operator=(const NonCopyable&) = delete;   // compile error if copy-assigned
    NonCopyable(NonCopyable&&) = default;                  // but still movable
    NonCopyable& operator=(NonCopyable&&) = default;
};

// = delete to block unwanted implicit conversions
void process(int x) { std::cout << "process(int): " << x << "\n"; }
void process(double) = delete; // calling process(3.14) now fails to compile,
                                 // instead of silently truncating to process(int)

int main() {
    Widget w1;          // uses = default ctor
    Widget w2(42);       // uses user-defined ctor
    std::cout << "w1.get()=" << w1.get() << " w2.get()=" << w2.get() << "\n";

    NonCopyable nc1;
    // NonCopyable nc2 = nc1;        // ERROR if uncommented: copy ctor is deleted
    NonCopyable nc2 = std::move(nc1); // OK: move is still = default
    (void)nc2;
    std::cout << "NonCopyable moved successfully\n";

    process(10);
    // process(3.14);  // ERROR if uncommented: call to deleted function process(double)

    return 0;
}
