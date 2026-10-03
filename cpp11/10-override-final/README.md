# override & final

## What problem did this solve?
Before C++11, overriding a virtual function was silently error-prone. A
tiny typo or signature mismatch (wrong const-ness, wrong parameter type)
created a **new, unrelated function** instead of overriding the base
version — and the compiler gave no warning:

```cpp
struct Base {
    virtual void draw(int x) const;
};
struct Derived : Base {
    virtual void draw(int x);  // BUG: missing 'const' -- this does NOT override!
                                 // It's a brand new overload. Silent bug.
};
```

## override — ask the compiler to verify
```cpp
struct Derived : Base {
    void draw(int x) const override; // compiler ERRORS if this doesn't actually override something
};
```
If the signature doesn't match a base virtual function exactly, you get a
**compile error** instead of silent, hard-to-debug incorrect behavior.
**Always use `override` on every intended override — no downside, free
safety net.**

## final — prevent further overriding/inheritance
```cpp
struct Derived : Base {
    void draw(int x) const final; // no further class may override draw()
};

struct Sealed final : Base { ... }; // no class may inherit from Sealed at all
```
Used for:
- API design (lock down a function/class's extension points deliberately)
- Performance: in some cases `final` enables devirtualization (compiler can
  resolve the call statically, skip the vtable lookup) since no further
  override is possible.

## Interview soundbite
> "`override` is purely a compile-time safety check — it has zero runtime
> effect; it just confirms your intent matches the base class signature.
> `final` prevents further overriding (on a function) or inheriting (on a
> class), and can be a minor performance win."

## Compile & run
```bash
g++ -std=c++11 -O2 -Wall src/example.cpp -o example && ./example
```
