// Variadic templates — real-time example
// Compile: g++ -std=c++11 -O2 -Wall example.cpp -o example

#include <iostream>
#include <memory>
#include <utility>

// Base case for recursion: empty pack
void print() { std::cout << "\n"; }

// Recursive unpacking: peel off T first, recurse on the rest
template <typename T, typename... Rest>
void print(T first, Rest... rest) {
    std::cout << first << " ";
    print(rest...);
}

// sizeof... usage
template <typename... Args>
void countArgs(Args... /*args*/) {
    std::cout << "Number of arguments: " << sizeof...(Args) << "\n";
}

// Real-world pattern: perfect-forwarding factory, like make_unique internals
struct Point {
    int x, y;
    Point(int x_, int y_) : x(x_), y(y_) {
        std::cout << "  Point(" << x << "," << y << ") constructed directly in place\n";
    }
};

template <typename T, typename... Args>
std::unique_ptr<T> makeUniqueDemo(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

int main() {
    std::cout << "--- Recursive variadic print ---\n";
    print(1, "two", 3.0, 'f');

    std::cout << "\n--- sizeof... ---\n";
    countArgs(1, 2, 3);
    countArgs("a", "b");
    countArgs();

    std::cout << "\n--- Perfect-forwarding factory (make_unique pattern) ---\n";
    auto p = makeUniqueDemo<Point>(10, 20); // args forwarded straight into Point's ctor
    std::cout << "Point: (" << p->x << "," << p->y << ")\n";

    return 0;
}
