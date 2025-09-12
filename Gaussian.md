# Gauss method

## [Linear combinations, span, and basis vectors](https://www.youtube.com/watch?v=k7RM-ot2NWY)
## [Basis and Dimension](https://www.youtube.com/watch?v=MMWqGD4Urso)

## [Gaussian Elimination](https://youtu.be/RgnWMBpQPXk?si=l0FAF1K1LW-cM7x5)


### 1. What is GF(2)? It's Just Fancy Talk for "Binary"

*   **GF(2)** stands for **"Galois Field of 2 elements"**. This sounds intimidating, but it's very simple. It just means a world where there are only two numbers: `0` and `1`.
*   The operations in this world are defined in a specific way:
    *   **Addition** is defined as **XOR** (`⊕`).
        *   `0 + 0 = 0`
        *   `0 + 1 = 1`
        *   `1 + 0 = 1`
        *   `1 + 1 = 0` (This is the key difference from normal math! 1 + 1 doesn't equal 2; it "wraps around" back to 0).
    *   **Multiplication** is defined as **AND** (`&`).
        *   `0 * 0 = 0`
        *   `0 * 1 = 0`
        *   `1 * 0 = 0`
        *   `1 * 1 = 1`

So when someone says "linear in GF(2)", they mean "we're working with binary numbers (0,1) and using XOR as addition".

---

### 2. The "Linear" Part: Thinking in Terms of Combinations

Let's say we have a set of binary numbers (e.g., `101`, `011`, `110`). A **linear combination** of these numbers in GF(2) means we pick a subset of them and XOR them together.

*   Example: The possible combinations of `{101, 011}` are:
    *   Take none: `000`
    *   Take first: `101`
    *   Take second: `011`
    *   Take both: `101 ⊕ 011 = 110`

The set of all possible XOR combinations you can create from a starting set of numbers is called the **span** of that set. It's the "vector space" the original quote mentions.

---

### 3. The "Basis"

A **basis** is a smallest possible set of *linearly independent* vectors (numbers) that can be used to generate every single number in the span. "Linearly independent" means no number in the set can be created by XORing some of the *other* numbers in the set. eg- i hat, j hat vectors

**Why is a basis useful?**
It's the most compact way to represent the entire space of possible XOR combinations. If you have a basis of size `k`, you know you can create exactly `2^k` unique numbers by XORing subsets of the basis.

---

### 4. [The Algorithm to Find the Basis](https://codeforces.com/blog/entry/68953)

This is the core of your question. **Gaussian Elimination is a systematic process for taking a set of vectors and whittling them down to a basis, removing all the redundant ones.**

Let's do it with a concrete example. Our goal is to process a list of numbers and end up with a basis stored in an array.

**The Rule:** We want our basis to be in **echelon form**. This means each basis vector has a leading `1` (the first `1` in its binary form) that is in a column where all other vectors have a `0`.

[XOR Space | Competitive Programming Winning Technique 2 | Gaussian Elimination | Vivek Gupta](https://youtu.be/qIXg9vJ6hZM?si=Ptmqv8hEUHkP-ESj&t=621)

```cpp
int basis[d + 1]; // basis[i] keeps the vector whose first set bit i

int sz; // Current size of the basis

void insertVector(int mask) {
	for (int i = d; i >= 0; i--) {
		if ((mask & 1 << i) == 0) continue;

        // If there is no basis vector with the i'th bit set, then insert this vector into the basis
		if (!basis[i]) { 
			basis[i] = mask;
			++sz;
			
			return;
		}

        // Otherwise subtract the basis vector from this vector
		mask ^= basis[i]; 
	}
}
```

1.  **Start with an empty basis.** Let's call our basis array `basis[]`. It's initially empty.
2.  **Process each number one by one.**
    *   For each number `x` in our list:
        *   **Let `temp = x`**
        *   **For each vector `b` already in the `basis` (from highest to lowest):**
            *   Check if the leading `1` of `b` is in the same bit position as a `1` in `temp`.
            *   If it is, we **cancel it out** by doing: `temp = temp XOR b`
            *   *Why?* Because if `temp` has a `1` in the same column as a basis vector `b`, we can use `b` to eliminate that `1` from `temp`.
        *   **After this process, what is `temp`?**
            *   If `temp == 0`: This means `x` was *not independent*. It was just a combination of the vectors we already have in the basis. We **discard it**.
            *   If `temp != 0`: This is a new, independent vector! We add `temp` to the basis. To maintain the echelon form, we often insert it in the correct position (so the basis vectors are sorted by their leading bit).

## Problem - Partition Array for Maximum XOR and AND - [my tutorial](https://leetcode.com/problems/partition-array-for-maximum-xor-and-and/solutions/7148287/the-ultimate-tutorial-gaussian-eliminati-qqob/)