# std::thread & Concurrency Basics

## What problem did this solve?
Before C++11, there was **no standard way to create threads at all** —
every platform required its own API (`pthread_create` on POSIX,
`CreateThread` on Windows). C++11 added a full concurrency library: threads,
mutexes, condition variables, atomics, futures/promises, and a formal
**memory model** that defines what "thread-safe" even means at the language
level.

## std::thread — basic usage
```cpp
#include <thread>

void work(int id) { std::cout << "thread " << id << "\n"; }

std::thread t(work, 42);  // starts running immediately
t.join();                  // block until t finishes (or t.detach() to let it run free)
```
**Every `std::thread` must be joined or detached before it's destroyed** —
otherwise `std::terminate()` is called. This is a very common interview
"spot the bug" question.

## std::mutex — mutual exclusion
```cpp
std::mutex m;
int counter = 0;

void increment() {
    m.lock();
    ++counter;
    m.unlock();
}
```
Manual `lock()`/`unlock()` is dangerous (exception between them = deadlock
forever). Always prefer RAII wrappers:

```cpp
void increment() {
    std::lock_guard<std::mutex> lock(m); // unlocks automatically, even on exception
    ++counter;
}
```

`std::lock_guard` = fixed scope, no manual unlock.
`std::unique_lock` = more flexible (can unlock early, works with condition
variables) but slightly more overhead.

## std::atomic — lock-free simple shared state
```cpp
std::atomic<int> counter{0};
counter++;  // thread-safe increment, no mutex needed
```
Use for simple counters/flags; use a mutex for protecting multi-step
invariants (atomics only guarantee the atomicity of a single operation).

## std::condition_variable — wait/notify
Lets one thread sleep until another thread signals that some condition
became true (classic producer/consumer pattern) — shown in the example.

## The data race rule (interview-critical)
> Unsynchronized concurrent access to the same memory, where at least one
> side is a write, is **undefined behavior** in C++11's memory model — not
> just "maybe wrong," but formally undefined. This is why `std::atomic` and
> mutexes aren't optional niceties; without them, the compiler is legally
> allowed to do anything.

## Compile & run
```bash
g++ -std=c++11 -O2 -Wall src/example.cpp -o example -pthread && ./example
```
(`-pthread` is required to link the threading library on Linux/g++.)
