### **Modular Inverse**
The **modular inverse** of an integer $a$ modulo $m$ is an integer $x$ such that:
$$ a \cdot x \equiv 1 \pmod{m} $$
This means $x$ is the multiplicative inverse of $a$ in the ring of integers modulo $m$.

A modular inverse $x$ exists **if and only if** $a$ and $m$ are **coprime** (i.e., $\gcd(a, m) = 1$).

### **Why Must $\gcd(a, m) = 1$?**
The above equation equivalent to:
$$ a \cdot x - m \cdot k = 1 \quad \text{(for some integer } k\text{)} $$

This is a **Linear Diophantine Equation (LDE)**:
$$ a x + m y = 1 \quad (\text{where } y = -k) $$

**Key Insight:**  
For integer solutions $(x, y)$, the **GCD** of $a$ and $m$ must divide both LHS & RHS =  $1$. But only $1$ divides $1$, so:
$$ \gcd(a, m) = 1 $$
**Thus, $a$ and $m$ must be coprime for an inverse to exist.**


## **Euclidean Algorithm**
$$ gcd(a,b)=gcd(b,a \mod b) $$
```
A: |-----b------|-----b------|-----b------|---r---|
B: |-----b------|

if something divides both A & B it should divide r as well.
```


## **Extended Euclidean Algorithm**
The **Extended Euclidean Algorithm (EEA)** is an extension of the standard **Euclidean Algorithm**. While the Euclidean Algorithm computes the **greatest common divisor (GCD)** of two integers $a$ and $b$, the EEA additionally finds integers $x$ and $y$ such that:

$$
\gcd(a, b) = g = a \cdot x + b \cdot y
$$

This equation is known as **Bézout's Identity**, and the coefficients $x$ and $y$ are called **Bézout coefficients**.

- $g$ is the smallest step/difference you can take on numberline using some combination of $a$ and $b$
[Visualization](https://youtu.be/ZUgzeUVsMME?si=iAVeuOwWiOi-al_W&t=136)

- You can solve for $x$ and $y$ using *Recursion* [[method](https://cp-algorithms.com/algebra/extended-euclid-algorithm.html#algorithm), [visualization](https://youtu.be/ZUgzeUVsMME?si=neJjgcFLdDQFVCLa&t=418)] or *Iteration* [[method](https://cp-algorithms.com/algebra/extended-euclid-algorithm.html#iterative-version), [visualization](https://www.youtube.com/watch?v=IwRtISxAHY4)]


## **[Linear Diophantine Equation](https://cp-algorithms.com/algebra/linear-diophantine-equation.html#linear-diophantine-equation) :** 

$$
a \cdot x + b \cdot y = c
$$

---


**Homogeneous linear Diophantine equation :**
$$
ax + by = 0
$$
where $a, b$ are integers, not both zero. Its solutions can be fully characterized using number theory.

It has **infinitely many integer solutions** $(x, y)$ given by:
$$
x = \frac{b}{\gcd(a, b)} \cdot k, \quad y = -\frac{a}{\gcd(a, b)} \cdot k, \quad \text{where } k \in \mathbb{Z}.
$$
#### **Explanation**:
1. **Divide by $\gcd(a, b)$**:  
   Let $g = \gcd(a, b)$. Then $a = g.a'$ and $b = g.b'$, where $\gcd(a', b') = 1$.  
   The equation becomes:
   $$
   g.a' x + g.b' y = 0 \implies a' x + b' y = 0.
   $$

2. **Solve the reduced equation**:  
   Since $\gcd(a', b') = 1$, we can write:
   $$
   a' x = -b' y.
   $$
   This implies $b' \mid a' x$, but since $\gcd(a', b') = 1$, we must have $b' \mid x$.  
   Let $x = b' k$ for some $k \in \mathbb{Z}$. Then:
   $$
   y = -a' k.
   $$
   
3. **General solution**:  
   Substituting back $a' = \frac{a}{g}$ and $b' = \frac{b}{g}$, we get:
   $$
   x = \frac{b}{g} \cdot k, \quad y = -\frac{a}{g} \cdot k.
   $$
---

#### **Geometric Interpretation**
The solutions $(x, y)$ lie on a straight line passing through the origin in $\mathbb{Z}^2$.  

The direction vector of the line is  
$$
\left( \frac{b}{\gcd(a, b)}, -\frac{a}{\gcd(a, b)} \right),
$$  
which is the **smallest integer direction** in which all solutions align.

---
- A degenerate case that need to be taken care of is when  
$a = b = 0$ . It is easy to see that we either have no solutions or infinitely many solutions, depending on whether  
$c = 0$  or not. In the rest of this article, we will ignore this case.
- Solution will only exist when $c$ is multiple of $g$, because the smallest step we can take is $g$. [Getting all solutions](https://cp-algorithms.com/algebra/linear-diophantine-equation.html#getting-all-solutions)

</br>
</br>
</br>
</br>

# TODO

## Euler's totient function
##  Chinese remainder theorem
## Fermat's little theorem
## Modular Multiplicative Inverse
