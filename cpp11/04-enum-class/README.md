# enum class (Scoped Enumerations)

## What problem did this solve?
Old C-style (unscoped) enums leaked their enumerators into the surrounding
scope and implicitly converted to `int`, causing name clashes and silent
bugs:

```cpp
enum Color { RED, GREEN, BLUE };
enum TrafficLight { RED, YELLOW, GREEN }; // ERROR: RED, GREEN redefined!

Color c = RED;
int x = c + 1;   // silently converts to int -- usually a mistake
```

## enum class fixes both problems
```cpp
enum class Color { Red, Green, Blue };
enum class TrafficLight { Red, Yellow, Green }; // OK, no clash — scoped

Color c = Color::Red;        // must qualify with the enum name
// int x = c + 1;             // ERROR: no implicit conversion to int
int x = static_cast<int>(c); // must be explicit
```

## Specifying the underlying type
Both scoped and unscoped enums (C++11 feature for both) can fix their
underlying integer type — useful for ABI stability / serialization:
```cpp
enum class Status : uint8_t { Ok = 0, Error = 1, Pending = 2 };
```

## Forward declaration
Because the underlying type can be fixed, enums can now be forward-declared
(impossible pre-C++11 since the compiler didn't know the size):
```cpp
enum class Direction : int; // forward declaration
```

## Interview soundbite
> "`enum class` gives you scoping (no namespace pollution) and strong typing
> (no implicit int conversion). Plain `enum` still exists for backward
> compatibility but should be avoided in new code."

## Compile & run
```bash
g++ -std=c++11 -O2 -Wall src/example.cpp -o example && ./example
```
