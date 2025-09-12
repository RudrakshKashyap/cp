# Fast Fourier transform

## Resources

- [Codeforces Blog from -is-this-fft-](https://codeforces.com/blog/entry/111371)
- [cp-algorithms.com](https://cp-algorithms.com/algebra/fft.html)
- [Visual FFT explanation YT video](https://www.youtube.com/watch?v=h7apO7q16V0)
- [Basic YT lecture by peltorator](https://codeforces.com/blog/entry/143282)


### Some Facts
1) Given $n$ pair of points $(x_0, y_0)$,$(x_1, y_1)$,…,$(x_{n-1}, y_{n-1})$
 where all the $n$ pairs are distinct, there is exactly one polynomial $P$
 with degree up to $n−1$
 such that $P(x_i$) = $y_i$ for each i. [proof](https://youtu.be/h7apO7q16V0?si=TMaRvNXz9VFMx5MP&t=285)
2) $$
   \text{DFT}\Big(\text{DFT}(c_0, c_1, \dots, c_{n-1})\Big) = \text{DFT}\big(C(\omega_0), \dots, C(\omega_{n-1})\big) = (n c_0, n c_{n-1}, n c_{n-2}, \dots, n c_1)
   $$

### Logic

Aim is to convert a polynomial from cofficient space(hard to multiply, $O(n^2)$) to value space. So we want $n$ distinct points that can represent our $n-1$ degree polynomial. We could have choosen any $n$ points but we will choose smartly [see](https://youtu.be/h7apO7q16V0?si=aw0ZFYsZaYSc-XWC&t=1051), so that our calculation gets reduced in half at every recursion call.


```cpp
// Recursive FFT implementation
vector<cd> fft(vector<cd> P) {
    int n = P.size();
    
    // Base case
    if (n == 1) return P;
    
    // Split into even and odd coefficients
    vector<cd> P_even(n / 2), P_odd(n / 2);
    for (int j = 0; j < n / 2; j++) {
        P_even[j] = P[2 * j];
        P_odd[j] = P[2 * j + 1];
    }
    
    // Recursive calls
    vector<cd> val_even = fft(P_even);
    vector<cd> val_odd = fft(P_odd);
    
    // Combine results
    vector<cd> val_P(n);
    for (int j = 0; j < n / 2; j++) {
        cd wj(cos(2 * pi * j / n), sin(2 * pi * j / n)); // e^(i*2πj/n)

        val_P[j] = val_even[j] + wj * val_odd[j];
        val_P[j + n / 2] = val_even[j] - wj * val_odd[j];
    }
    
    return val_P;
}
```
---
```cpp
//Simply reverse of fft function
vector<cd> ifft(vector<cd> val_P) {
    int n = val_P.size();
    if (n == 1) return val_P;

    vector<cd> val_even(n / 2), val_odd(n / 2);
    for (int j = n / 2 - 1; j >= 0; j--) {
        cd wj = polar(1.0, 2 * pi * j / n);
        
        val_even[j] = (val_P[j] + val_P[j + n / 2]) / 2.0;
        val_odd[j] = (val_P[j] - val_P[j + n / 2]) / (2.0 * wj);
    }
    
    vector<cd> P_even = ifft(val_even);
    vector<cd> P_odd = ifft(val_odd);
    
    vector<cd> P(n);
    for (int j = n / 2 - 1; j >= 0; j--) {
        P[2 * j] = P_even[j];
        P[2 * j + 1] = P_odd[j];
    }
    
    return P;
}
```
---
```cpp
vector<long long> multiply(vector<int>& P, vector<int>& Q) {
    vector<cd> P_cd(P.begin(), P.end()), Q_cd(Q.begin(), Q.end());

    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    P_cd.resize(n);
    Q_cd.resize(n);

    vector<cd> P_val = fft(P_cd);
    vector<cd> Q_val = fft(Q_cd);
    vector<cd> R_val(n);

    for (int i = 0; i < n; i++)
        R_val[i] = P_val[i] * Q_val[i];

    vector<cd> R_cd = ifft(R_val);

    vector<long long> R(n);
    for (int i = 0; i < n; i++)
        R[i] = round(R_cd[i].real());

    return R;
}
```
<br />
<br />
<br />

# Number theoretic transform (NTT) -- TODO