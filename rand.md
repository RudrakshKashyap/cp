https://codeforces.com/blog/entry/61587

## Problem with rand()

The rand() function returns an integer between 0 and RAND_MAX.
RAND_MAX is a constant defined in <cstdlib> and is typically 32767 (the maximum value for a 16-bit signed integer).
The sequence of numbers generated by rand() depends on the seed value.

The seed can be set using the srand() function.

If you don't set a seed, rand() will use a default seed (usually 1), producing the same sequence of numbers every time the program runs.

```cpp
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    srand(time(0));  //Seeds the pseudo-random number generator used by std::rand() with the value seed.

    int lower_bound = 10;
    int upper_bound = 20;

    // Generate a random number between 10 and 20
    int random_number = lower_bound + (rand() % (upper_bound - lower_bound + 1));
    std::cout << "Random number between 10 and 20: " << random_number << std::endl;

    return 0;
}
```
It doesn't stop there though; random_shuffle() also uses rand().

## Solution - Mersenne Twister:

It has a very long period of 
`2^19937 −1`, which means it can generate a huge number of random values before repeating the sequence.

`std::mt19937`
This is a specific implementation of the Mersenne Twister algorithm in C++.
It generates 32-bit unsigned integers (uint32_t).


 `std::uniform_int_distribution`
Generates random integers within a specified range [a,b] Each integer in the range has an equal probability of being generated.

```cpp
#include <iostream>
#include <random>

int main() {
    std::random_device rd;  // Seed generator
    std::mt19937 gen(rd()); // Mersenne Twister engine

    // Define a uniform integer distribution between 1 and 100
    std::uniform_int_distribution<> dist(1, 100);

    // Generate a random number
    int random_number = dist(gen);

    std::cout << "Random number: " << random_number << std::endl;

    return 0;
}
```
`std::uniform_int_distribution` cannot work without a random number engine. The random number engine (e.g., `std::mt19937`) is essential because it provides the source of randomness, while the distribution (e.g., `std::uniform_int_distribution`) shapes that randomness into the desired range and statistical properties.

The distribution (e.g., `std::uniform_int_distribution`) does not generate random numbers on its own. Instead, it transforms the raw numbers from the engine into the desired range and distribution.


| Feature                     | `std::random_device`                          | `time(0)`                          |
|-----------------------------|-----------------------------------------------|------------------------------------|
| **Randomness Quality**      | High (true randomness)                        | Low (predictable)                  |
| **Entropy Source**          | Hardware (e.g., CPU instructions, system noise)| System clock (seconds since epoch) |
| **Unpredictability**        | High (suitable for security-sensitive apps)   | Low (easy to guess)                |
| **Seed Range**              | Large (depends on implementation)             | Limited (32-bit or 64-bit integer) |
| **Portability**             | Works consistently across platforms           | Works everywhere but less reliable |
| **Performance**             | May be slower (depends on hardware)           | Very fast                          |





