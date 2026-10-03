# Uniform Initialization & std::initializer_list

## What problem did this solve?
C++98 had many different, inconsistent initialization syntaxes:
```cpp
int x = 5;
int arr[3] = {1, 2, 3};
std::vector<int> v(3, 0);     // 3 elements, each 0 -- not {0,1,2}!
Widget w(1, 2);
Widget w2;                     // default -- but Widget w2(); is a FUNCTION DECLARATION! (most vexing parse)
```
C++11 introduced **brace initialization** `{}` as a single, consistent
syntax usable almost everywhere:
```cpp
int x{5};
int arr[3]{1, 2, 3};
Widget w{1, 2};
Widget w2{};                   // unambiguously default-constructs, no vexing parse
```

## The "most vexing parse" — a real interview trap
```cpp
Widget w2();   // Looks like default construction... but C++ parses this as
                // a FUNCTION DECLARATION named w2 returning Widget!
Widget w2{};    // Brace init has no such ambiguity -- always construction.
```

## Narrowing conversion protection
Brace init **forbids narrowing conversions** at compile time — a safety
feature `()` and `=` don't have:
```cpp
int x = 3.14;   // silently truncates to 3, no warning in most compilers
int y{3.14};     // ERROR: narrowing conversion from double to int
```

## std::initializer_list — the mechanism behind {1,2,3}
```cpp
#include <initializer_list>
class MyVector {
public:
    MyVector(std::initializer_list<int> list) {
        for (int x : list) data_.push_back(x);
    }
private:
    std::vector<int> data_;
};

MyVector v{1, 2, 3, 4}; // calls the initializer_list constructor
```
This is literally how `std::vector<int> v{1,2,3}` works — `vector` has a
constructor overload taking `std::initializer_list<T>`.

## The classic gotcha: {} vs () with constructors that have an initializer_list overload
```cpp
std::vector<int> a(3, 7);  // Parens -> calls (size_t count, T value) ctor -> {7,7,7}
std::vector<int> b{3, 7};  // Braces -> PREFERS initializer_list ctor if one exists -> {3,7}
```
**This is one of the most common real interview questions on this topic** —
when an `initializer_list` constructor exists, brace-init prefers it over
other overloads, even if another overload would otherwise be a better match.

## Compile & run
```bash
g++ -std=c++11 -O2 -Wall src/example.cpp -o example && ./example
```
