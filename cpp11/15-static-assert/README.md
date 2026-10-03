# static_assert

## What problem did this solve?
`assert()` from `<cassert>` only checks conditions **at runtime** — the
program has to actually execute the check. For things that are knowable at
**compile time** (template parameter properties, sizeof assumptions, type
traits), you want the build to fail immediately with a clear message,
rather than shipping broken code that fails (or silently misbehaves) only
when some code path runs.

## Syntax
```cpp
static_assert(constant_expression, "error message string");
```
If `constant_expression` evaluates to `false` at compile time, compilation
**fails** with your custom message. If `true`, it's a complete no-op — zero
runtime cost.

## Common real-world uses

**1. Validating template parameters**
```cpp
template <typename T>
class FixedBuffer {
    static_assert(std::is_trivially_copyable<T>::value,
                  "FixedBuffer requires a trivially copyable type");
    // ...
};
```

**2. Sanity-checking assumptions about sizes/layout**
```cpp
struct NetworkPacket {
    uint32_t header;
    uint8_t  payload[12];
};
static_assert(sizeof(NetworkPacket) == 16, "NetworkPacket must be exactly 16 bytes for wire format");
```

**3. Checking platform assumptions**
```cpp
static_assert(sizeof(void*) == 8, "This code requires a 64-bit platform");
```

**4. Combined with type traits (`<type_traits>`)**
```cpp
template <typename T>
T add(T a, T b) {
    static_assert(std::is_arithmetic<T>::value, "T must be a numeric type");
    return a + b;
}
```

## static_assert vs assert — interview comparison table
| | `static_assert` | `assert` |
|---|---|---|
| Checked | Compile time | Runtime |
| Cost | Zero (compile-time only) | Runtime branch (usually stripped in release via NDEBUG) |
| Failure | Compilation error | Program abort (if reached) |
| Usable on | Constant expressions only | Any boolean expression |

## Compile & run
```bash
g++ -std=c++11 -O2 -Wall src/example.cpp -o example && ./example
```
(The file also includes commented-out lines that intentionally fail
`static_assert` — uncomment them to see the compile-time error.)
