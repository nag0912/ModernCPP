# Range-based for loops

## What problem did this solve?
Iterating a container required verbose, error-prone iterator boilerplate:
```cpp
for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) { ... }
```
C++11 added syntax that works for arrays, STL containers, and any type
exposing `begin()`/`end()`.

## Syntax & how it desugars
```cpp
for (auto& x : container) { ... }
```
is equivalent to:
```cpp
{
    auto&& __range = container;
    for (auto __it = begin(__range); __it != end(__range); ++__it) {
        auto& x = *__it;
        ...
    }
}
```
Note it calls unqualified `begin()`/`end()` — found via ADL (argument
dependent lookup) or the container's own member functions. This is why you
can make **your own types** range-for-compatible just by providing
`begin()`/`end()` (members or free functions).

## Value category choices — the interview trap
```cpp
for (auto x : v)   // COPY of each element — safe, but wasteful for big objects
for (auto& x : v)  // REFERENCE — can modify, no copy
for (const auto& x : v) // read-only reference — the usual default for non-trivial types
```
Rule of thumb for interviews: **default to `const auto&` unless you need to
mutate or the type is cheap to copy (int, double, small structs).**

## Works on raw arrays too
```cpp
int arr[5] = {1,2,3,4,5};
for (auto x : arr) { ... }   // works! array size is known at compile time
```

## Custom iterable types
Any class with `begin()`/`end()` returning something supporting `!=`, `++`,
and `*` works in range-for — this is how custom ranges, generators, and
containers hook in.

## Compile & run
```bash
g++ -std=c++11 -O2 -Wall src/example.cpp -o example && ./example
```
