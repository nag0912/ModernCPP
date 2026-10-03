# Lambdas

## What problem did this solve?
Before C++11, passing custom logic to algorithms (`std::sort`, `std::for_each`)
meant writing a named function or a function-object (functor) class
elsewhere in the file — far from where it's used:

```cpp
struct IsEven { bool operator()(int x) const { return x % 2 == 0; } };
std::count_if(v.begin(), v.end(), IsEven());
```

Lambdas let you write the logic **inline**, at the call site:
```cpp
std::count_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
```

## Anatomy of a lambda
```cpp
[capture](params) mutable -> return_type { body }
```
- `capture` — what from the enclosing scope is visible inside
- `params` — like a normal function's parameters
- `mutable` — optional; allows modifying captured-by-value variables inside the lambda
- `-> return_type` — optional; usually deduced automatically
- `body` — the code

## Capture modes — the part interviewers love to probe

```cpp
int x = 10;

[]() {}         // captures nothing
[x]() {}        // capture x BY VALUE (copy, frozen at lambda creation time)
[&x]() {}       // capture x BY REFERENCE (sees live changes, dangling risk if x dies first)
[=]() {}        // capture everything used, by value
[&]() {}        // capture everything used, by reference
[=, &x]() {}    // default by value, but x specifically by reference
[&, x]() {}     // default by reference, but x specifically by value
```

**Danger case (common interview question):** returning a lambda that
captures by reference leads to a dangling reference once the local variable
goes out of scope:
```cpp
auto makeBad() {
    int local = 42;
    return [&local]() { return local; }; // DANGLING -- local is destroyed
}
```

## What is a lambda, really?
The compiler turns each lambda into an **unnamed class (closure type)** with
`operator()` overloaded, and captured variables become its member fields.
This is why two lambdas with identical code still have *different types* —
useful to know for template contexts.

## Storing lambdas: auto vs std::function
```cpp
auto l = [](int x) { return x * 2; };       // exact closure type, zero overhead
std::function<int(int)> f = l;              // type-erased, has overhead but can be reassigned/stored uniformly
```
Use `auto` when you can; use `std::function` when you need a uniform type
(e.g. a vector of callbacks with different internal captures).

## Compile & run
```bash
g++ -std=c++11 -O2 -Wall src/example.cpp -o example && ./example
```
