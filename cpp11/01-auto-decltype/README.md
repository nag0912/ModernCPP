# auto & decltype

## What problem did this solve?

Before C++11, every variable's type had to be spelled out explicitly — including
monstrosities like:
```cpp
std::map<std::string, std::vector<int>>::iterator it = myMap.begin();
```
`auto` lets the compiler deduce the type from the initializer:
```cpp
auto it = myMap.begin();
```

`decltype` is the companion feature: it yields the *type* of an expression
without evaluating it — essential for generic/template code where you don't
know types in advance.

## auto — deduction rules

`auto` uses the **same deduction rules as template argument deduction**. That
has real consequences:

```cpp
int x = 10;
int& ref = x;
const int& cref = x;

auto a = ref;     // int   (reference stripped)
auto b = cref;     // int   (const AND reference stripped)
auto& c = cref;    // const int&  (now it's preserved, because you asked for a reference)
auto&& d = 10;     // int&&  (universal/forwarding reference in template context)
```

**Common interview trap:** `auto` by itself strips `const` and `&`. If you
want to keep them, you must write `const auto&` or `auto&` explicitly.

```cpp
std::vector<int> v = {1,2,3};
for (auto x : v) x *= 2;      // modifies COPIES, v unchanged!
for (auto& x : v) x *= 2;     // modifies v correctly
```

## decltype — exact type, no stripping

```cpp
int x = 10;
int& rx = x;
decltype(rx) y = x;   // y is int&  (decltype preserves reference-ness exactly)
```

`decltype(expr)`:
- If `expr` is a plain variable name → gives its declared type.
- If `expr` is any other expression (like `(x)` with parens, or a function
  call) → gives `T&` if the expression is an lvalue, `T` if it's a prvalue.

```cpp
int x = 0;
decltype(x) a;     // int
decltype((x)) b = x; // int&   <-- the extra parens change everything!
```

This "parens matter" rule is a classic interview gotcha.

## decltype(auto) (mentioned here, fully C++14)
Combines both: deduces like `decltype`, but written like `auto`. Useful for
writing generic forwarding functions where you want to preserve exact
value category of the return expression. Covered in depth under C++14.

## trailing return type (co-introduced with auto in C++11)
```cpp
template<typename T, typename U>
auto add(T t, U u) -> decltype(t + u) {
    return t + u;
}
```
Needed before C++14 because the return type depends on parameters that
aren't in scope until after the parameter list.

## Compile & run
```bash
g++ -std=c++11 -O2 -Wall src/example.cpp -o example && ./example
```
