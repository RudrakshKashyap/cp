> Since ternary op returns lvalue ref, you can do something like `(cond ? x : y)++;`

```cpp
// This is a syntax feature introduced in C++17 called if with initializer.
// The same syntax works with switch statements
if (init-statement; condition) 

if (int x = getValue(); x > 0) {
    std::cout << "Positive: " << x << std::endl;
}
// x is automatically destroyed here

```