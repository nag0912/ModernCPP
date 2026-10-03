# Generic Lambdas

## What problem did this solve?
In C++11, lambda parameters needed concrete types:
```cpp
auto add = [](int a, int b) { return a + b; }; // only works for int
```
If you wanted the same logic for `double`, `std::string`, etc., you needed
either a separate lambda per type, or a hand-written functor template. C++14
lets you use `auto` for lambda parameters, making the lambda itself
effectively a template.

## Syntax
```cpp
auto add = [](auto a, auto b) { return a + b; };

add(1, 2);          // T = int
add(1.5, 2.5);       // T = double
add(std::string("a"), std::string("b")); // T = std::string
```

## What's really happening
The compiler turns this into a closure type with a **templated**
`operator()`:
```cpp
struct __lambda_closure {
    template <typename T1, typename T2>
    auto operator()(T1 a, T2 b) const { return a + b; }
};
```
Each call site with different argument types instantiates a different
specialization — exactly like a function template, just written inline.

## Note: the two auto parameters can deduce to DIFFERENT types
```cpp
auto f = [](auto a, auto b) { return a + b; };
f(1, 2.5); // a deduced as int, b deduced as double -- fine, not required to match
```
If you want them to be forced to the *same* type, you'd write it as an
explicit function template instead.

## Real-world use: generic comparators/predicates
```cpp
auto byAbs = [](auto a, auto b) { return std::abs(a) < std::abs(b); };
std::sort(intVec.begin(), intVec.end(), byAbs);
std::sort(doubleVec.begin(), doubleVec.end(), byAbs); // same lambda, different type
```

## Compile & run
```bash
g++ -std=c++14 -O2 -Wall src/example.cpp -o example && ./example
```
