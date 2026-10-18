# BigInt Algorithms

## 1. Representation

Represent an integer as

$$
N = s\sum_{i=0}^{n-1} d_i 10^i
$$

where:

- $s \in \{-1,1\}$ is the sign.
- $d_i \in \{0,\ldots,9\}$ is a decimal digit.
- $d_0$ is the least significant digit.

For example, $-4207$ is represented as:

$$
s=-1,\qquad D=[7,0,2,4]
$$

## 2. Normalization

Normalization ensures that each integer has a consistent representation.

- Remove unnecessary most-significant zeros.
- Ensure at least one digit remains.
- Represent zero as $D=[0]$ with $s=1$.

## 3. Absolute Comparison

To compare $|a|$ and $|b|$:

1. Compare their digit counts. The number with more digits has the greater magnitude.
2. If their digit counts are equal, compare digits from most significant to least significant.

Return $1$, $0$, or $-1$ when the first magnitude is greater than, equal to, or less than the second.

## 4. Addition

For each digit, calculate the sum and carry:

$$
t=a_i+b_i+c_i
$$

The resulting digit and outgoing carry are:

$$
r_i=t\bmod 10
$$

$$
c_{i+1}=\left\lfloor\frac{t}{10}\right\rfloor
$$

For signed integers:

- **Same signs:** Add the magnitudes and keep the common sign.
- **Different signs:** Subtract the smaller magnitude from the larger and keep the sign of the larger magnitude.
- **Equal magnitudes with opposite signs:** Return zero.

## 5. Subtraction

Subtraction can be implemented using negation and addition:

$$
a-b=a+(-b)
$$

Negate $b$ by reversing its sign, then apply the addition algorithm.

## 6. Subtraction of Magnitudes

Assume $|a|\ge |b|$. For each digit, calculate:

$$
t_i=a_i-b_i-\operatorname{borrow}_i
$$

If $t_i<0$:

$$
r_i=t_i+10,\qquad
\operatorname{borrow}_{i+1}=1
$$

Otherwise:

$$
r_i=t_i,\qquad
\operatorname{borrow}_{i+1}=0
$$

Continue until all digits have been processed, then normalize the result.

## 7. Multiplication

Grade-school multiplication computes the product by multiplying every pair of digits and accumulating the partial products.

For digits at positions $i$ and $j$:

$$
t=r_{i+j}+a_i b_j+c
$$

Update the result digit and carry:

$$
r_{i+j}=t\bmod 10
$$

$$
c=\left\lfloor\frac{t}{10}\right\rfloor
$$

The product sign is:

$$
s_{ab}=s_a s_b
$$

For operands with $m$ and $n$ digits, the time complexity is:

$$
O(mn)
$$

## 8. Division

Use long division on the absolute values of the operands.

Process the dividend digits from most significant to least significant. For each digit $d$:

1. Bring down the next digit:

   $$
   R\leftarrow 10R+d
   $$

2. Find the largest quotient digit $q\in\{0,\ldots,9\}$ satisfying:

   $$
   q|b|\le R
   $$

3. Subtract the corresponding multiple of the divisor:

   $$
   R\leftarrow R-q|b|
   $$

The quotient sign is:

$$
s_q=s_a s_b
$$

Integer division truncates toward zero. Division by zero must be rejected.

The division invariant is:

$$
|a|=|b|Q+R,\qquad 0\le R<|b|
$$

where $Q$ and $R$ are the nonnegative quotient magnitude and remainder.

## 9. Comparison Operators

- **Different signs:** A positive integer is always greater than a negative integer.
- **Both positive:** Compare magnitudes normally.
- **Both negative:** Reverse the magnitude comparison.
- **Equality:** Both signs and magnitudes must match.

Zero must always be normalized to a positive sign.

## 10. Random Generation

To generate an $n$-digit decimal integer:

1. Generate each digit in $\{0,\ldots,9\}$.
2. Ensure the most significant digit is nonzero:

   $$
   d_{n-1}\ne0
   $$

3. Optionally choose a sign:

   $$
   s\in\{-1,1\}
   $$

Reject $n=0$, since a valid decimal integer must contain at least one digit.

## 11. Input and Output

Digits are stored in reverse order, so output them from the last element to the first:

$$
d_{n-1},d_{n-2},\ldots,d_0
$$

Print `-` before the digits when the integer is negative.

## 12. Correctness Checks

Basic arithmetic operations should satisfy the following identities for all integers $a$ and $b$:

**Addition identity**

$$
a+0=a
$$

**Subtraction identity**

$$
a-a=0
$$

**Multiplication by zero**

$$
a\cdot0=0
$$

For $b\ne0$, integer division must satisfy:

$$
a=bq+r,\qquad |r|<|b|
$$

Here, $q$ is the quotient truncated toward zero, and $r$ has the same sign as the dividend or is zero.
