# = default & = delete

## What problem did this solve?
Two separate old pains:

1. **Forcing compiler-generated functions explicitly.** If you declared any
   constructor, the compiler stopped auto-generating the default
   constructor. Pre-C++11, if you still wanted it, you had to write an empty
   body by hand (`Foo() {}`) — easy to get subtly wrong vs the real
   compiler-generated version (e.g. member initialization order).

2. **Preventing copying.** The classic C++98 trick to make a class
   non-copyable was declaring copy ctor/assignment `private` and never
   defining them — a link-time or (if used inside the class) only a vague
   "function is private" error, discovered late and with poor diagnostics.

## = default — explicitly request the compiler's version
```cpp
class Widget {
public:
    Widget() = default;              // still get the compiler-generated default ctor
    Widget(int x) : x_(x) {}         // user-defined ctor -- without the line above,
                                       // this alone would suppress the default ctor
private:
    int x_;
};
```
Also works for copy/move ctor, copy/move assignment, destructor — lets you
be explicit about wanting the compiler's version alongside other
customizations, rather than relying on implicit rules that are easy to
misremember.

## = delete — explicitly forbid
```cpp
class NonCopyable {
public:
    NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete;            // clear compile-time error if copied
    NonCopyable& operator=(const NonCopyable&) = delete;
};
```
Attempting to copy now fails **at compile time** with a clear message
("function is deleted"), rather than a vague private-access error.

`= delete` also works on **any** function, not just special members — handy
for blocking unwanted implicit conversions:
```cpp
void process(int x);
void process(double) = delete; // calling process(3.14) is now a compile error,
                                 // instead of silently truncating to int
```

## Interview soundbite
> "`= default` and `= delete` make the compiler's special-member-function
> generation **explicit and intentional** instead of relying on implicit
> rules that are easy to get wrong (especially once you add any
> user-declared constructor or destructor)."

## Compile & run
```bash
g++ -std=c++11 -O2 -Wall src/example.cpp -o example && ./example
```
