# Function Return Type Deduction (auto) & decltype(auto)

## What problem did this solve?
C++11 allowed `auto` return types only via the trailing-return-type syntax,
and *still* required you to spell out the return type expression yourself
(`-> decltype(...)`):
```cpp
template <typename T, typename U>
auto add(T t, U u) -> decltype(t + u) { return t + u; } // C++11
```
C++14 allows the compiler to deduce the return type **purely from the
`return` statement(s)** — no trailing return type needed at all:
```cpp
template <typename T, typename U>
auto add(T t, U u) { return t + u; } // C++14: deduced automatically
```

## Deduction rules — same as auto variables (strips references/const)
```cpp
auto getValue() { return 42; }        // returns int
auto& getRef();                        // trailing & still needed if you want a reference return

const std::string& getName();
auto getName2() { return getName(); } // returns std::string BY VALUE (auto strips const & ref!)
```
**Interview trap:** if a function returns a reference internally via
`return someRef;`, plain `auto` as the return type still deduces a
**value**, copying the referenced object — not what you usually want if the
intent was to return a reference.

## decltype(auto) — preserves exact type including references
```cpp
const std::string& getName();
decltype(auto) getName2() { return getName(); } // returns const std::string& (preserved!)
```
`decltype(auto)` uses `decltype` deduction rules (exact, including
reference-ness) instead of `auto`'s rules (strips reference/const). This
matters a lot for generic wrapper functions that need to forward a return
value/reference exactly as-is.

## Multiple return statements must agree
```cpp
auto pick(bool b) {
    if (b) return 1;
    else return 2.0;   // ERROR: deduced types (int vs double) must match across all returns
}
```

## Compile & run
```bash
g++ -std=c++14 -O2 -Wall src/example.cpp -o example && ./example
```
