### **R-4.7**

To determine $n_0$ where Algorithm A ($8n \log n$) is better than Algorithm B ($2n^2$), we solve for $8n \log n < 2n^2$. Dividing both sides by $2n$ results in $4 \log n < n$.

- At **$n = 16$**: $4 \log_2(16) = 16$. The operations are equal.
- At **$n = 17$**: $4 \log_2(17) \approx 16.35$, which is less than 17.
  Since the linear side ($n$) grows faster than the logarithmic side, Algorithm A remains more efficient for all $n \ge 17$.
  **Result:** **$n_0 = 17$**.

---

### **R-4.8**

To find $n_0$ where Algorithm A ($40n^2$) is better than Algorithm B ($2n^3$), we solve for $40n^2 < 2n^3$. Dividing both sides by $2n^2$ yields $20 < n$.

- The inequality is strictly satisfied when $n$ is greater than 20.
- The smallest integer satisfying this condition is 21.
  **Result:** **$n_0 = 21$**.

---

### **R-4.13**

The functions are ordered by their dominant terms as $n$ approaches infinity:

1.  **$2^{10}$**: Constant growth.
2.  **$2^{\log n}$**: Simplifies to $n$ (Linear).
3.  **$3n + 100 \log n$** and **$4n$**: Both are Linear, though $4n$ has a larger coefficient.
4.  **$n \log n$** and **$4n \log n + 2n$**: Both are Linearithmic.
5.  **$n^2 + 10n$**: Quadratic growth.
6.  **$n^3$**: Cubic growth.
7.  **$2^n$**: Exponential growth.
    **Order:** $2^{10} < 2^{\log n} < 3n + 100 \log n < 4n < n \log n < 4n \log n + 2n < n^2 + 10n < n^3 < 2^n$.

---

### **R-4.18**

The `Ex3` function's running time is determined by its nested loop structure:

- The outer loop runs $n$ times ($i = 0$ to $n-1$).
- The inner loop runs $i$ times ($j = 1$ to $i$) for each iteration of $i$.
- The total number of operations is represented by the summation: $\sum_{i=0}^{n-1} i = \frac{n(n-1)}{2}$.
  Asymptotically, the $n^2$ term dominates the expression.
  **Result:** **$O(n^2)$**.
