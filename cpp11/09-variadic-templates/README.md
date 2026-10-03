# Variadic Templates

## What problem did this solve?
Pre-C++11, a function/template accepting "any number of arguments of any
types" required either C-style varargs (`...`, type-unsafe, no destructors
run on args) or a painful wall of overloads (`f(a)`, `f(a,b)`, `f(a,b,c)`...
up to some arbitrary limit). Variadic templates allow genuinely arbitrary,
type-safe parameter packs.

## Basic syntax
```cpp
template <typename... Args>   // Args is a "template parameter pack"
void f(Args... args) {        // args is a "function parameter pack"
    // ...
}
```
`sizeof...(Args)` gives the pack size at compile time.

## Classic pattern: recursive unpacking
C++11 has no fold expressions (that's C++17), so you peel off one argument
at a time via recursive overloads:

```cpp
void print() {} // base case: empty pack

template <typename T, typename... Rest>
void print(T first, Rest... rest) {
    std::cout << first << " ";
    print(rest...);  // recurse with one fewer argument
}
```

## Real-world use: std::make_unique-style perfect forwarding
```cpp
template <typename T, typename... Args>
std::unique_ptr<T> makeUnique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
```
This is essentially how `std::make_shared`/`make_unique` work internally:
the parameter pack is forwarded, preserving each argument's value category,
directly into the constructor — no intermediate copies.

## sizeof... and compile-time checks
```cpp
template <typename... Args>
void checkCount(Args... args) {
    static_assert(sizeof...(args) <= 5, "Too many arguments!");
}
```

## Interview soundbite
> "Variadic templates generalize templates to accept any number of
> arguments of any types, resolved entirely at compile time via recursive
> instantiation. C++17's fold expressions later made the recursive
> boilerplate unnecessary for common cases."

## Compile & run
```bash
g++ -std=c++11 -O2 -Wall src/example.cpp -o example && ./example
```
