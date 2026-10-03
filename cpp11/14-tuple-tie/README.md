# std::tuple & std::tie

## What problem did this solve?
Functions returning more than one value had awkward options pre-C++11: a
struct defined just for this one purpose, out-parameters (pass pointers/refs
in), or `std::pair` (only 2 elements). `std::tuple` generalizes `pair` to
**any number of heterogeneous values**.

## std::tuple basics
```cpp
#include <tuple>

std::tuple<int, std::string, double> t(1, "hello", 3.14);

int i = std::get<0>(t);          // access by INDEX (compile-time constant)
std::string s = std::get<1>(t);
double d = std::get<2>(t);

std::get<0>(t) = 99; // get<> returns a reference -- can modify too
```
Access is by **compile-time index** (`std::get<N>`), not runtime index —
this is why it works for heterogeneous types; the compiler needs to know
the type at each position.

## std::make_tuple — type deduction helper
```cpp
auto t = std::make_tuple(1, "hello", 3.14); // deduces tuple<int, const char*, double>
```

## std::tie — unpacking a tuple into existing variables
```cpp
int id;
std::string name;
std::tie(id, name) = someFunctionReturningTuple();
```
`std::tie` creates a tuple of **references** to the given variables, then
tuple assignment copies each element in. Use `std::ignore` to skip fields
you don't care about:
```cpp
std::tie(id, std::ignore) = someFunctionReturningPair();
```

## Real-world pattern: returning multiple values from a function
```cpp
std::tuple<bool, std::string> parseConfig(const std::string& path) {
    if (!exists(path)) return std::make_tuple(false, "");
    return std::make_tuple(true, readFile(path));
}

bool ok; std::string content;
std::tie(ok, content) = parseConfig("config.txt");
```

## Comparing tuples
`tuple` has built-in lexicographic comparison operators (`<`, `==`, etc.) —
compares element by element, like comparing words alphabetically. Handy for
sorting by multiple keys:
```cpp
std::vector<std::tuple<int,int>> points = {{3,1},{1,5},{1,2}};
std::sort(points.begin(), points.end()); // sorts by first element, then second
```

## Note: C++17 made this nicer
Structured bindings (`auto [id, name] = someFunction();`) make `std::tie`
largely unnecessary for simple unpacking in C++17+ — but you'll still see
`std::tie` constantly in real codebases and interview questions about
pre-C++17 code.

## Compile & run
```bash
g++ -std=c++11 -O2 -Wall src/example.cpp -o example && ./example
```
