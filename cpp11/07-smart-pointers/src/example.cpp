// Smart pointers — real-time example
// Compile: g++ -std=c++11 -O2 -Wall example.cpp -o example

#include <iostream>
#include <memory>
#include <cstdio>

struct Widget {
    int id;
    explicit Widget(int i) : id(i) { std::cout << "Widget(" << id << ") created\n"; }
    ~Widget() { std::cout << "Widget(" << id << ") destroyed\n"; }
};

// --- weak_ptr example: breaking a reference cycle ---
struct B; // fwd
struct A {
    std::shared_ptr<B> bptr;
    ~A() { std::cout << "A destroyed\n"; }
};
struct B {
    std::weak_ptr<A> aptr; // weak_ptr breaks the cycle -- would leak if shared_ptr
    ~B() { std::cout << "B destroyed\n"; }
};

int main() {
    std::cout << "--- unique_ptr: exclusive ownership ---\n";
    {
        std::unique_ptr<Widget> u(new Widget(1)); // C++14: std::make_unique<Widget>(1)
        // std::unique_ptr<Widget> u2 = u;         // ERROR: copy ctor deleted
        std::unique_ptr<Widget> u2 = std::move(u); // OK: ownership transferred
        std::cout << "u is now " << (u ? "non-null" : "null") << "\n";
    } // u2 goes out of scope here -> Widget(1) destroyed automatically

    std::cout << "\n--- shared_ptr: reference counted ---\n";
    {
        std::shared_ptr<Widget> s1 = std::make_shared<Widget>(2);
        std::cout << "refcount after s1 created: " << s1.use_count() << "\n";
        {
            std::shared_ptr<Widget> s2 = s1;
            std::cout << "refcount after s2 = s1: " << s1.use_count() << "\n";
        } // s2 destroyed, refcount drops
        std::cout << "refcount after s2 scope ends: " << s1.use_count() << "\n";
    } // s1 destroyed -> refcount 0 -> Widget(2) destroyed

    std::cout << "\n--- weak_ptr: breaking a cycle ---\n";
    {
        auto a = std::make_shared<A>();
        auto b = std::make_shared<B>();
        a->bptr = b;    // A holds a shared_ptr to B
        b->aptr = a;    // B holds a weak_ptr to A -- does NOT bump A's refcount

        std::cout << "A refcount: " << a.use_count() << " (1, not 2 -- weak_ptr doesn't count)\n";

        if (auto locked = b->aptr.lock()) {
            std::cout << "Locked weak_ptr successfully, A is still alive\n";
        }
    } // both a and b destroyed cleanly -- no leak, because B held a weak_ptr not shared_ptr

    std::cout << "\n--- custom deleter: RAII for non-'new' resources ---\n";
    {
        // Using a lambda as a custom deleter to wrap a C-style FILE* resource
        std::unique_ptr<FILE, void(*)(FILE*)> file(
            fopen("/tmp/smartptr_demo.txt", "w"),
            [](FILE* f) { if (f) { std::cout << "Closing file via custom deleter\n"; fclose(f); } }
        );
        if (file) fputs("hello from smart pointer RAII\n", file.get());
    } // file automatically closed here, even if an exception had been thrown

    std::cout << "\n--- end of main ---\n";
    return 0;
}
