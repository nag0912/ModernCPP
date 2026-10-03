# constexpr

## What problem did this solve?
Pre-C++11, compile-time computation required ugly template metaprogramming
tricks (recursive templates instantiated at compile time). `constexpr` lets
you write **normal-looking functions** that the compiler can evaluate at
compile time when given compile-time-constant inputs.

## constexpr variables
```cpp
constexpr int size = 10;      // must be initialized with a constant expression
int arr[size];                // usable as an array bound (needs compile-time value)
```
Different from `const`: a `const int x = someRuntimeValue;` is legal but `x`
isn't usable where a compile-time constant is required. `constexpr` demands
it.

## constexpr functions (C++11 restrictions)
In C++11, a constexpr function body was very restricted: essentially a
**single return statement** (no loops, no multiple statements, no local
variables). This was relaxed significantly in C++14 (see that section).

```cpp
constexpr int square(int x) {
    return x * x; // C++11: body must reduce to a single return
}

constexpr int result = square(5); // computed at COMPILE time
int arr[square(4)];               // usable as array size
```

## Recursive constexpr (the C++11 workaround for no loops)
```cpp
constexpr int factorial(int n) {
    return n <= 1 ? 1 : n * factorial(n - 1); // recursion instead of a loop
}
```

## constexpr can also run at runtime
If the compiler can't prove the inputs are compile-time constants, a
`constexpr` function just runs normally at runtime — it's not an error:
```cpp
int x = readFromUser();
int y = square(x); // runs at runtime, totally fine
```

## constexpr vs const (classic interview question)
| | `const` | `constexpr` |
|---|---|---|
| Meaning | "I promise not to modify this" | "This is known at compile time" |
| Initializer | can be runtime value | must be a constant expression |
| Usable as array bound / template arg | only if happens to be compile-time | always |

## Compile & run
```bash
g++ -std=c++11 -O2 -Wall src/example.cpp -o example && ./example
```
