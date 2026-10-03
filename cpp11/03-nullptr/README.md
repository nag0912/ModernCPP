# nullptr

## What problem did this solve?
Pre-C++11, people used `NULL` (usually `#define NULL 0`) or plain `0` for
null pointers. Both are actually **integers**, not pointers — which causes
real overload-resolution bugs.

```cpp
void f(int x);
void f(char* p);

f(NULL);  // Which overload? NULL is often just 0 -> calls f(int)!
          // Programmer almost certainly wanted f(char*)
```

This is a classic interview question: *"Why is `nullptr` better than `NULL`
or `0`?"*

## nullptr is its own type
`nullptr` has type `std::nullptr_t`. It converts implicitly to any pointer
type, and to `bool`, but **not** to integral types like `int`. This makes
overload resolution unambiguous:

```cpp
f(nullptr);  // unambiguously calls f(char*)
```

## Template deduction benefits too
```cpp
template <typename T>
void g(T t);

g(NULL);     // T deduced as int (or long) — wrong intent
g(nullptr);  // T deduced as std::nullptr_t — correctly represents "null pointer"
```

## Comparisons still work as expected
```cpp
int* p = nullptr;
if (p == nullptr) { ... }   // fine
if (!p) { ... }             // fine, nullptr converts to bool false
```

## Compile & run
```bash
g++ -std=c++11 -O2 -Wall src/example.cpp -o example && ./example
```
