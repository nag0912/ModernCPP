// Uniform initialization & initializer_list — real-time example
// Compile: g++ -std=c++11 -O2 -Wall example.cpp -o example

#include <iostream>
#include <vector>
#include <initializer_list>

struct Widget {
    int a, b;
    Widget() : a(0), b(0) { std::cout << "Widget default ctor\n"; }
    Widget(int a_, int b_) : a(a_), b(b_) { std::cout << "Widget(" << a << "," << b << ")\n"; }
};

// Custom class demonstrating how initializer_list constructors work
class MyVector {
    std::vector<int> data_;
public:
    MyVector(std::initializer_list<int> list) {
        std::cout << "MyVector(initializer_list) called with " << list.size() << " elements\n";
        for (int x : list) data_.push_back(x);
    }
    void print() const {
        for (int x : data_) std::cout << x << " ";
        std::cout << "\n";
    }
};

int main() {
    // --- Most vexing parse avoided with {} ---
    Widget w1{};        // unambiguous default construction
    Widget w2(1, 2);     // normal paren construction
    Widget w3{3, 4};     // brace construction, same effect as parens here
    (void)w1; (void)w2; (void)w3;

    // --- Narrowing conversion protection ---
    int x = 3.9;   // allowed (with potential compiler warning): x becomes 3
    // int y{3.9};  // ERROR if uncommented: narrowing conversion double -> int
    std::cout << "x (from int x = 3.9) = " << x << "\n";

    // --- () vs {} with std::vector: THE classic gotcha ---
    std::vector<int> a(3, 7);  // parens -> (count, value) ctor -> three 7s
    std::vector<int> b{3, 7};  // braces -> PREFERS initializer_list ctor -> {3, 7}

    std::cout << "vector a(3,7)  = ";
    for (int v : a) std::cout << v << " ";
    std::cout << "  (3 copies of 7)\n";

    std::cout << "vector b{3,7}  = ";
    for (int v : b) std::cout << v << " ";
    std::cout << "  (literally the values 3 and 7)\n";

    // --- Custom initializer_list constructor ---
    MyVector mv{10, 20, 30};
    mv.print();

    return 0;
}
