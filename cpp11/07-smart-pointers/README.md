# Smart Pointers (unique_ptr, shared_ptr, weak_ptr)

## What problem did this solve?
Manual `new`/`delete` is error-prone: forget a `delete` → leak; delete twice
→ crash; exception thrown between `new` and `delete` → leak. RAII (Resource
Acquisition Is Initialization) ties a resource's lifetime to an object's
scope — smart pointers apply RAII to heap memory specifically.

`std::auto_ptr` (C++98) tried to solve this but had broken copy semantics
(copying transferred ownership silently) and was deprecated/removed.

## std::unique_ptr — exclusive ownership
```cpp
std::unique_ptr<Widget> p = std::make_unique<Widget>(args); // C++14 for make_unique
```
- Exactly one `unique_ptr` owns the object at a time.
- **Cannot be copied** (copy constructor deleted) — only **moved**.
- Zero overhead vs a raw pointer (no refcount).
- Automatically deletes the object when it goes out of scope.

```cpp
std::unique_ptr<int> a(new int(5));
std::unique_ptr<int> b = a;            // ERROR: copy is deleted
std::unique_ptr<int> b = std::move(a); // OK: ownership transferred, a is now null
```

## std::shared_ptr — shared ownership, reference counted
```cpp
std::shared_ptr<Widget> p1 = std::make_shared<Widget>(args);
std::shared_ptr<Widget> p2 = p1; // refcount now 2
```
- Internally holds a pointer to the object + a control block with an atomic
  reference count.
- Object destroyed when the **last** `shared_ptr` owning it is destroyed.
- `make_shared` is preferred over `shared_ptr<T>(new T(...))` — it does a
  **single allocation** for object + control block (vs two separate
  allocations), better cache locality, exception-safer.

## std::weak_ptr — non-owning observer
Solves the **circular reference** problem: if A holds a `shared_ptr` to B and
B holds a `shared_ptr` back to A, neither refcount ever reaches zero — a
memory leak. A `weak_ptr` doesn't contribute to the refcount; you must
`.lock()` it to get a temporary `shared_ptr` (or null if the object is gone)
before using it.

```cpp
std::weak_ptr<Widget> weak = sharedPtr;
if (auto locked = weak.lock()) {
    // locked is a valid shared_ptr, object still alive
} else {
    // object has already been destroyed
}
```

## Interview soundbite
> "`unique_ptr` for exclusive ownership (default choice, zero overhead).
> `shared_ptr` when multiple owners genuinely need to share lifetime.
> `weak_ptr` to break cycles or observe without extending lifetime. Avoid
> raw `new`/`delete` entirely in modern code."

## Custom deleters
```cpp
std::unique_ptr<FILE, decltype(&fclose)> file(fopen("x.txt", "r"), &fclose);
```
Smart pointers aren't just for `new`/`delete` — they generalize RAII to any
resource with an acquire/release pair.

## Compile & run
```bash
g++ -std=c++11 -O2 -Wall src/example.cpp -o example && ./example
```
(Note: `make_unique` was added in C++14 — the example constructs
`unique_ptr` directly to stay strictly C++11-compatible, but a comment shows
the C++14 alternative.)
