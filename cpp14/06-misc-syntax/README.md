# Misc C++14 Syntax: Binary Literals, Digit Separators, Variable Templates, [[deprecated]]

Small quality-of-life additions, still worth knowing for interviews since
they show up in real codebases constantly.

## Binary literals
```cpp
int flags = 0b1010'1100; // C++14: write binary directly with 0b prefix
```
Pre-C++14 you had to use hex (`0xAC`) and mentally convert, or compute it at
runtime with bit-shifts.

## Digit separators (')
```cpp
int million = 1'000'000;         // readability, purely cosmetic -- ' is ignored by the compiler
long bigHex = 0xFFFF'FFFF'FFFF'FFFFL;
double pi   = 3.14159'26535;
```
The `'` can go anywhere between digits — it has zero effect on the value,
purely for human readability of long numeric literals.

## Variable templates
```cpp
template <typename T>
constexpr T pi = T(3.1415926535897932385);

float  f = pi<float>;   // instantiates the float version
double d = pi<double>;  // instantiates the double version
```
Before this, you'd need a function (`pi<T>()`) or a static class member —
variable templates let you template a *value* directly, not just functions
and classes. The standard library uses this heavily in `<type_traits>` from
C++17 onward (`std::is_same_v<T,U>` is a variable template built on
`is_same<T,U>::value`).

## [[deprecated]] attribute
```cpp
[[deprecated("use newFunction() instead")]]
void oldFunction();
```
Produces a compiler warning (not error) at every call site — the standard,
portable way to mark an API as discouraged without breaking existing builds
immediately. (Attributes like `[[nodiscard]]` came later in C++17, but
`[[deprecated]]` itself is a C++14 addition.)

## Compile & run
```bash
g++ -std=c++14 -O2 -Wall src/example.cpp -o example && ./example
```
