// override & final — real-time example
// Compile: g++ -std=c++11 -O2 -Wall example.cpp -o example

#include <iostream>

struct Shape {
    virtual void draw() const { std::cout << "Shape::draw\n"; }
    virtual ~Shape() = default;
};

struct Circle : Shape {
    // override forces the compiler to verify this really overrides Shape::draw.
    // Try changing the signature (e.g. add a parameter, or drop 'const') --
    // it will fail to compile instead of silently creating a new function.
    void draw() const override { std::cout << "Circle::draw\n"; }
};

struct FilledCircle final : Circle {
    // final: no further class may override draw() beyond this point
    void draw() const override final { std::cout << "FilledCircle::draw\n"; }
};

struct SealedBase final {
    void whoAmI() const { std::cout << "SealedBase (class is final, cannot be inherited)\n"; }
};
// struct Derived : SealedBase {}; // ERROR if uncommented: SealedBase is final

int main() {
    Shape* shapes[] = { new Shape(), new Circle(), new FilledCircle() };
    for (auto* s : shapes) {
        s->draw(); // virtual dispatch -- correct override picked at runtime
    }
    for (auto* s : shapes) delete s;

    SealedBase sb;
    sb.whoAmI();

    return 0;
}
