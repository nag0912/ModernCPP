# Rvalue References & Move Semantics

## What problem did this solve?
Pre-C++11, returning or passing large objects (vectors, strings) by value
always meant a full deep copy, even when the source was a temporary about to
be destroyed anyway. There was no way to say "this object is disposable —
just steal its guts instead of copying them."

## Value categories (quick primer)
- **lvalue** — has a name/address, persists beyond the expression (`x`, `*p`, `v[0]`)
- **rvalue** — temporary, about to be destroyed (`5`, `x + y`, a function's
  by-value return)

```cpp
int x = 10;     // x is an lvalue
int y = x + 1;  // (x + 1) is an rvalue
```

## Rvalue reference syntax
```cpp
int&  lref = x;        // binds to lvalues only
int&& rref = x + 1;    // binds to rvalues only (extends temporary's lifetime)
```

## The golden rule: named rvalue references are themselves lvalues
```cpp
void foo(std::string&& s) {
    bar(s);             // s is a NAMED variable -> it's an lvalue here!
                          // calls bar(const string&), NOT bar(string&&)
    bar(std::move(s));   // explicitly cast back to rvalue -> calls bar(string&&)
}
```
`std::move` does nothing at runtime — it's just `static_cast<T&&>(x)`. It's a
*permission slip* telling the compiler "treat this as disposable," enabling
move-constructor/move-assignment overload resolution.

## Move constructor & move assignment
See the full walkthrough and `Buffer` RAII example in `src/example.cpp` —
copy constructor deep-copies (`O(n)`), move constructor steals the pointer
(`O(1)`) and leaves the source in a valid-but-empty state.

## Rule of Five
If you define any of: destructor, copy ctor, copy assign, move ctor, move
assign — you usually need to think about **all five**. Define a custom
destructor and the compiler stops auto-generating move operations for you.

## Why mark move operations noexcept
`std::vector` only uses your move constructor during reallocation if it's
`noexcept`. Otherwise, to preserve the strong exception guarantee, it falls
back to copying (silently losing your performance win). Always mark move
operations `noexcept` when they can't throw.

## std::forward (perfect forwarding) — related, template-only feature
```cpp
template <typename T>
void wrapper(T&& arg) {            // universal/forwarding reference (T deduced)
    inner(std::forward<T>(arg));   // preserves arg's original value category
}
```
`T&&` in a **template** with `T` deduced is a *forwarding reference*, not a
plain rvalue reference — it can bind to both lvalues and rvalues. This is
different from `std::string&&` (concrete type), which only binds to rvalues.
`std::forward` passes the argument along exactly as it was received
(lvalue stays lvalue, rvalue stays rvalue) — essential for generic
wrapper/factory functions.

## Compile & run
```bash
g++ -std=c++11 -O2 -Wall src/example.cpp -o example && ./example
```
