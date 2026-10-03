# std::make_unique

## What problem did this solve?
C++11 shipped `std::unique_ptr` and `std::make_shared`, but **forgot**
`std::make_unique` (famously called an oversight by Herb Sutter) — it was
added in C++14 to complete the symmetry.

## Why not just write `unique_ptr<T>(new T(...))`?
```cpp
std::unique_ptr<Widget> p(new Widget(1, 2)); // works, but has a real exception-safety issue
```

### The exception-safety problem (classic interview question)
Consider a function call with two arguments, each requiring their own
`unique_ptr`:
```cpp
void process(std::unique_ptr<Widget> a, std::unique_ptr<Widget> b);

process(std::unique_ptr<Widget>(new Widget(1)),
        std::unique_ptr<Widget>(new Widget(2)));
```
The compiler is **not required** to evaluate these in a fixed left-to-right
order — it could, in principle, interleave the `new` calls and the
`unique_ptr` constructor calls like this:
```
new Widget(1)
new Widget(2)
unique_ptr ctor for a
unique_ptr ctor for b
```
If the second `new Widget(2)` throws **after** the first `new Widget(1)`
succeeded but **before** it was wrapped in its `unique_ptr`, the first
`Widget` leaks — nothing owns it yet, and no destructor will run.

### make_unique fixes this entirely
```cpp
process(std::make_unique<Widget>(1), std::make_unique<Widget>(2));
```
Each `make_unique<Widget>(...)` call performs the `new` and the ownership
wrap **as a single, atomic-looking function call** — there's no window where
a raw, un-owned pointer could leak due to another argument's exception.

## Syntax
```cpp
auto p = std::make_unique<Widget>(arg1, arg2); // perfectly forwards args to Widget's ctor
```

## Interview soundbite
> "Prefer `make_unique`/`make_shared` over direct `unique_ptr<T>(new T(...))`
> both for conciseness and for exception safety — they eliminate the
> 'naked new' window where a raw pointer briefly exists unowned."

## Compile & run
```bash
g++ -std=c++14 -O2 -Wall src/example.cpp -o example && ./example
```
