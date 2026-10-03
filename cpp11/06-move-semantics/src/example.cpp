// Move semantics — real-time example
// Compile: g++ -std=c++11 -O2 -Wall example.cpp -o example

#include <iostream>
#include <utility> // std::move, std::forward
#include <algorithm>

class Buffer {
    int* data;
    size_t size;
public:
    explicit Buffer(size_t n) : data(new int[n]), size(n) {
        std::cout << "  [ctor] allocated " << size << " ints\n";
    }

    // Copy constructor -- expensive, deep copy
    Buffer(const Buffer& other) : size(other.size) {
        data = new int[size];
        std::copy(other.data, other.data + size, data);
        std::cout << "  [copy ctor] deep-copied " << size << " ints\n";
    }

    // Move constructor -- cheap, steals the pointer
    Buffer(Buffer&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        std::cout << "  [move ctor] stole pointer, O(1)\n";
    }

    // Move assignment
    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
            std::cout << "  [move assign] stole pointer\n";
        }
        return *this;
    }

    // Copy assignment
    Buffer& operator=(const Buffer& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            std::copy(other.data, other.data + size, data);
            std::cout << "  [copy assign] deep-copied\n";
        }
        return *this;
    }

    ~Buffer() {
        if (data) std::cout << "  [dtor] freeing " << size << " ints\n";
        else std::cout << "  [dtor] freeing empty (moved-from) buffer\n";
        delete[] data;
    }

    size_t getSize() const { return size; }
};

Buffer makeBuffer() {
    Buffer b(1000000);
    return b; // move (or RVO-elided entirely by the compiler)
}

// Demonstrates the "named rvalue ref is an lvalue" rule
void inner(std::string&& s) {
    std::cout << "  inner() received: " << s << "\n";
}
void wrongForward(std::string&& s) {
    std::cout << "wrongForward: passing s without move (s is an lvalue here)\n";
    // inner(s); // would fail to bind to inner(string&&) -- s is an lvalue in this scope
}
void correctForward(std::string&& s) {
    std::cout << "correctForward: passing std::move(s)\n";
    inner(std::move(s)); // explicitly cast back to rvalue
}

// Perfect forwarding with a template
template <typename T>
void relay(T&& arg) {            // forwarding reference (T deduced)
    inner(std::forward<T>(arg)); // preserves original value category
}

int main() {
    std::cout << "--- Copy vs Move constructor ---\n";
    Buffer a(5);
    std::cout << "Copying a into b:\n";
    Buffer b = a;                 // copy constructor
    std::cout << "Moving a into c:\n";
    Buffer c = std::move(a);      // move constructor; a is now empty
    std::cout << "a.getSize() after move = " << a.getSize() << " (moved-from)\n";

    std::cout << "\n--- Move from a factory function ---\n";
    Buffer d = makeBuffer();      // move or RVO

    std::cout << "\n--- Named rvalue ref is itself an lvalue ---\n";
    correctForward("hello");

    std::cout << "\n--- Perfect forwarding via std::forward ---\n";
    relay(std::string("forwarded-temp")); // rvalue forwarded as rvalue

    std::cout << "\n--- End of main, destructors fire in reverse order ---\n";
    return 0;
}
