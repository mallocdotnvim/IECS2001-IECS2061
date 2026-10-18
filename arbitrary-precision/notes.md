# BigInt Arithmetic

## 1. Representation

Represent an integer using a sign and a digit array.

$$
A=s_A|A|,\qquad s_A\in\{-1,+1\}
$$

For base $B$, the magnitude is:

$$
|A|=\sum_{i=0}^{n-1}a_iB^i
$$

where $0\le a_i<B$.

For example, with $B=10$, the integer $1234$ is stored in little-endian order as `[4, 3, 2, 1]`.

## 2. `compare_abs(a, b)`

Compare magnitudes without considering signs.

- Different digit lengths: the longer number has the greater magnitude.
- Equal lengths: compare digits from most significant to least significant.
- All digits equal: magnitudes are equal.

$$
\operatorname{compare\_abs}(a,b)
\begin{cases}
>0 & |a|>|b|\\
=0 & |a|=|b|\\
<0 & |a|<|b|
\end{cases}
$$

**Time complexity:** $O(n)$.

## 3. `add_abs(a, b)`

Add magnitudes using carry propagation.

For each digit position:

$$
t_i=a_i+b_i+c_i
$$

$$
r_i=t_i\bmod B
$$

$$
c_{i+1}=\left\lfloor\frac{t_i}{B}\right\rfloor
$$

Initially, $c_0=0$. Append the final carry if nonzero.

Example:

$$
789+156=945
$$

**Time complexity:** $O(n)$.

## 4. `sub_abs(a, b)`

Subtract magnitudes using borrowing. Requires $|a|\ge|b|$.

For each digit position:

$$
t_i=a_i-b_i-q_i
$$

If $t_i<0$:

$$
r_i=t_i+B,\qquad q_{i+1}=1
$$

Otherwise:

$$
r_i=t_i,\qquad q_{i+1}=0
$$

Initially, $q_0=0$. Remove leading zeros from the result.

Example:

$$
502-178=324
$$

**Time complexity:** $O(n)$.

## 5. `add(a, b)`

Let $a=s_a|a|$ and $b=s_b|b|$.

**Same signs:** add magnitudes and preserve the sign.

$$
s_a=s_b\implies
a+b=s_a(|a|+|b|)
$$

**Different signs:** subtract the smaller magnitude from the larger and use the sign of the operand with the larger magnitude.

$$
|a|>|b|\implies
a+b=s_a(|a|-|b|)
$$

$$
|a|<|b|\implies
a+b=s_b(|b|-|a|)
$$

$$
|a|=|b|\implies a+b=0
$$

**Time complexity:** $O(n)$.

## 6. `sub(a, b)`

Subtraction is addition with the second operand negated.

$$
\boxed{a-b=a+(-b)}
$$

For nonzero $b$, reverse its sign and call `add(a, -b)`. Zero remains non-negative.

Examples:

$$
15-20=-5
$$

$$
(-15)-(-8)=-7
$$

**Time complexity:** $O(n)$.

## 7. `mult(a, b)`

Grade-school multiplication computes partial products.

$$
|a|=\sum_{i=0}^{n-1}a_iB^i
$$

$$
|b|=\sum_{j=0}^{m-1}b_jB^j
$$

Therefore:

$$
|a||b|=
\sum_{i=0}^{n-1}\sum_{j=0}^{m-1}
a_ib_jB^{i+j}
$$

Each digit product contributes to position $i+j$. Accumulate the products, propagate carries, and normalize the result.

The result sign is:

$$
s_R=s_as_b
$$

If either operand is zero, return zero.

Example:

$$
123\times45=5535
$$

**Time complexity:**

$$
O(nm)
$$

For similarly sized operands, this is $O(n^2)$.

## 8. `div(a, b)`

Integer division calculates a quotient $q$ and remainder $r$:

$$
\boxed{a=bq+r}
$$

Division by zero must be rejected.

### Long division

Process the dividend from most significant digit to least significant digit. At each step, bring down the next digit:

$$
r_{\text{temp}}=Br_{\text{old}}+d_i
$$

Choose the largest quotient digit $q_i$ satisfying:

$$
q_i|b|\le r_{\text{temp}}
$$

Update the remainder:

$$
r_{\text{new}}=r_{\text{temp}}-q_i|b|
$$

The quotient digits form the final quotient.

For truncation toward zero:

$$
|q|=\left\lfloor\frac{|a|}{|b|}\right\rfloor
$$

$$
s_q=s_as_b
$$

The remainder satisfies:

$$
|r|<|b|
$$

If nonzero, its sign matches the dividend's sign.

Example:

$$
17=5(3)+2
$$

$$
-17=5(-3)+(-2)
$$

The quotient is $3$ and $-3$, respectively.

## 9. Correctness invariants

- **Digit range:** $0\le a_i<B$.
- **Canonical zero:** zero is never negative.
- **Addition:** $a+b=b+a$.
- **Subtraction:** $a-b=a+(-b)$.
- **Multiplication:** $ab=ba$.
- **Division:** $a=bq+r$, with $|r|<|b|$ for nonzero $b$.

All magnitude operations assume normalized operands. `sub_abs(a, b)` additionally requires $|a|\ge|b|$.