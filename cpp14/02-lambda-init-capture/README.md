# Lambda Init-Capture (Generalized Capture)

## What problem did this solve?
C++11 lambda captures could only copy or reference an **existing** variable
by its own name — you couldn't capture a renamed or computed expression, and
critically, **you couldn't move a move-only type (like `unique_ptr`) into a
lambda**:

```cpp
std::unique_ptr<Widget> p = ...;
auto l = [p]() { ... };          // ERROR in C++11: unique_ptr can't be copied
auto l = [&p]() { ... };          // compiles, but now the lambda depends on p's lifetime
```

## Syntax: name = expression
```cpp
auto l = [newName = expression]() { ... };
```
This declares a **new variable** inside the closure, initialized from
`expression`, evaluated at the point the lambda is created.

## The headline use case: moving into a lambda
```cpp
std::unique_ptr<Widget> p = std::make_unique<Widget>();
auto l = [p = std::move(p)]() {   // move the unique_ptr INTO the closure
    p->doSomething();
};
// p (outer) is now null -- ownership transferred into the lambda's closure
```
This is the standard C++14 idiom for giving a lambda **exclusive ownership**
of a resource — essential for async callbacks, thread lambdas, and
task-queue patterns where the original scope ends before the lambda runs.

## Gotcha: move-capturing lambdas can't go in std::function
A lambda that move-captures a `unique_ptr` becomes itself **non-copyable**
(its implicit copy constructor is deleted, since it has a non-copyable
member). But `std::function` requires its target to be copy-constructible —
so storing such a lambda in `std::function` fails to compile. You either
call it directly/pass it by auto, or reach for `std::move_only_function`
(added in C++23) as the type-erased equivalent for move-only callables.

## Also useful for renaming / precomputing
```cpp
int x = 10;
auto l = [y = x * 2]() { return y; }; // capture a COMPUTED value, not x itself
```

## Compile & run
```bash
g++ -std=c++14 -O2 -Wall src/example.cpp -o example && ./example
```
