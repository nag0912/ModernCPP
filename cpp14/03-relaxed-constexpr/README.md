# Relaxed constexpr

## What problem did this solve?
C++11's `constexpr` functions were restricted to essentially **one return
statement** — no local variables, no loops, no if/else, no multiple
statements. Any non-trivial compile-time computation required awkward
recursion (see the C++11 `factorial` example). C++14 relaxed these rules
dramatically.

## What's now allowed inside constexpr functions
- Local variable declarations (with initializers)
- Loops (`for`, `while`, `do-while`)
- Conditionals (`if`, `else`, `switch`)
- Multiple statements, including multiple `return`s
- Mutation of local variables

```cpp
// C++11: had to use recursion
constexpr int factorial11(int n) {
    return n <= 1 ? 1 : n * factorial11(n - 1);
}

// C++14: can write it like ordinary code
constexpr int factorial14(int n) {
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}
```
Both are evaluated at compile time when given compile-time-constant
arguments — C++14's version is just dramatically easier to write and read.

## Why this matters for interviews
A very common question: *"What changed about constexpr between C++11 and
C++14?"* Answer: **C++11 constexpr functions are essentially pure, single-
expression functions (like a mathematical formula); C++14 constexpr
functions can look like ordinary imperative code** (loops, local state,
branches) while still being evaluable at compile time.

## Still true in both versions
- The function must still be *capable* of producing a constant expression
  for *some* set of arguments (not every call needs to be compile-time).
- If called with non-constant arguments, it simply runs at runtime like a
  normal function — no different from C++11 in that respect.

## Compile & run
```bash
g++ -std=c++14 -O2 -Wall src/example.cpp -o example && ./example
```
