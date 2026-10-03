# Modern C++ Interview Prep (C++11 → C++23)

A structured, interview-focused walkthrough of every major Modern C++ feature,
organized by language standard. Each topic has:
- A detailed `README.md` explaining the concept, *why it was introduced*, and common interview traps
- A compilable `src/example.cpp` with a real-world-style example

## How to use this repo
```bash
cd cpp11/06-move-semantics/src
g++ -std=c++11 -O2 -Wall example.cpp -o example
./example
```
Each topic's README has the exact compile command (flags/standard) at the bottom.

---

## Table of Contents

### [C++11](./cpp11/README.md) — the big revolution
| # | Topic | Folder |
|---|-------|--------|
| 1 | auto & decltype | [01-auto-decltype](./cpp11/01-auto-decltype) |
| 2 | Range-based for loops | [02-range-based-for](./cpp11/02-range-based-for) |
| 3 | nullptr | [03-nullptr](./cpp11/03-nullptr) |
| 4 | enum class (scoped enums) | [04-enum-class](./cpp11/04-enum-class) |
| 5 | Lambdas | [05-lambdas](./cpp11/05-lambdas) |
| 6 | Rvalue refs & move semantics | [06-move-semantics](./cpp11/06-move-semantics) |
| 7 | Smart pointers | [07-smart-pointers](./cpp11/07-smart-pointers) |
| 8 | constexpr | [08-constexpr](./cpp11/08-constexpr) |
| 9 | Variadic templates | [09-variadic-templates](./cpp11/09-variadic-templates) |
| 10 | override & final | [10-override-final](./cpp11/10-override-final) |
| 11 | default & delete | [11-default-delete](./cpp11/11-default-delete) |
| 12 | Uniform init & initializer_list | [12-uniform-init](./cpp11/12-uniform-init) |
| 13 | std::thread & concurrency basics | [13-threads](./cpp11/13-threads) |
| 14 | tuple & tie | [14-tuple-tie](./cpp11/14-tuple-tie) |
| 15 | static_assert | [15-static-assert](./cpp11/15-static-assert) |

### [C++14](./cpp14/README.md) — polish release
| # | Topic | Folder |
|---|-------|--------|
| 1 | Generic lambdas | [01-generic-lambdas](./cpp14/01-generic-lambdas) |
| 2 | Lambda init-capture | [02-lambda-init-capture](./cpp14/02-lambda-init-capture) |
| 3 | Relaxed constexpr | [03-relaxed-constexpr](./cpp14/03-relaxed-constexpr) |
| 4 | std::make_unique | [04-make-unique](./cpp14/04-make-unique) |
| 5 | Return type deduction & decltype(auto) | [05-return-type-deduction](./cpp14/05-return-type-deduction) |
| 6 | Misc syntax (binary literals, var templates, etc.) | [06-misc-syntax](./cpp14/06-misc-syntax) |

### C++17 — *coming next*
optional/variant/any, structured bindings, if/switch init, filesystem, fold expressions, constexpr-if, CTAD, [[nodiscard]]

### C++20 — *coming next*
Concepts, Ranges, Coroutines, Modules, span, format, spaceship operator, consteval/constinit, designated initializers

### C++23 — *coming next*
expected, mdspan, print/println, if consteval, deducing this, stacktrace

---

## Status
- [x] C++11 (complete)
- [x] C++14 (complete)
- [ ] C++17
- [ ] C++20
- [ ] C++23
