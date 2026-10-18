# BigInt Algorithms

## 1. Representation

Represent an integer as

$$
N = s\sum_{i=0}^{n-1} d_i 10^i
$$

where:
- \(s \in \{-1,1\}\) is the sign.
- \(d_i \in \{0,\ldots,9\}\) is a decimal digit.
- \(d_0\) is the least significant digit.

Example: \(-4207\) is represented by \(s=-1\) and \(D=[7,0,2,4]\).

## 2. Normalization

- Remove leading zeros.
- Keep at least one digit.
- Represent zero as \(s=1\) and \(D=[0]\).

## 3. Absolute Comparison

To compare \(|a|\) and \(|b|\):

1. Compare digit counts.
2. If equal, compare digits from most significant to least significant.

Return \(1\), \(0\), or \(-1\) if the first magnitude is greater than, equal to, or less than the second.

## 4. Addition

For each digit, compute the sum and carry:

$$
t = a_i + b_i + c_i
$$

$$
r_i = t \bmod 10,\qquad
c_{i+1} = \left\lfloor \frac{t}{10} \right\rfloor
$$

For signed integers:

- Same signs: add magnitudes and keep the common sign.
- Different signs: subtract the smaller magnitude from the larger and keep the sign of the larger magnitude.
- Equal magnitudes: return zero.

## 5. Subtraction

Use negation and addition:

$$
a-b=a+(-b)
$$

Negate \(b\) by reversing its sign, then apply the addition algorithm. Normalize zero to a positive sign.

## 6. Magnitude Subtraction

Assume \(|a|\ge |b|\). For each digit, compute

$$
t_i=a_i-b_i-\operatorname{borrow}_i
$$

If \(t_i<0\):

$$
r_i=t_i+10,\qquad
\operatorname{borrow}_{i+1}=1
$$

Otherwise:

$$
r_i=t_i,\qquad
\operatorname{borrow}_{i+1}=0
$$

Process all digits, then normalize the result.

## 7. Multiplication

Grade-school multiplication accumulates partial products. For digit positions \(i\) and \(j\):

$$
t=r_{i+j}+a_i b_j+c
$$

$$
r_{i+j}=t\bmod 10,\qquad
c=\left\lfloor\frac{t}{10}\right\rfloor
$$

The product sign is

$$
s_{ab}=s_a s_b
$$

For operands with \(m\) and \(n\) digits, the time complexity is

$$
O(mn)
$$

## 8. Division

Perform long division on the absolute values. Process the dividend digits from most significant to least significant.

For each digit \(d\):

1. Bring down the digit:

   $$
   R\leftarrow 10R+d
   $$

2. Find the largest quotient digit \(q\in\{0,\ldots,9\}\) satisfying

   $$
   q|b|\le R
   $$

3. Update the remainder:

   $$
   R\leftarrow R-q|b|
   $$

The quotient sign is \(s_q=s_a s_b\). Integer division truncates toward zero. Division by zero must be rejected.

The division invariant is

$$
|a|=|b|Q+R,\qquad 0\le R<|b|
$$

where \(Q\) and \(R\) are the nonnegative quotient magnitude and remainder.

## 9. Comparison Operators

- Different signs: positive is greater than negative.
- Both positive: compare magnitudes normally.
- Both negative: reverse the magnitude comparison.
- Equality: compare normalized signs and magnitudes.

Zero must always have a positive sign.

## 10. Random Generation

To generate an \(n\)-digit integer:

1. Require \(n\ge1\).
2. Generate each digit \(d_i\in\{0,\ldots,9\}\).
3. Ensure the most significant digit is nonzero:

   $$
   d_{n-1}\ne0
   $$

4. Optionally choose \(s\in\{-1,1\}\).

## 11. Input and Output

Digits are stored in reverse order. Print them from \(d_{n-1}\) to \(d_0\), prepending `-` if the integer is negative.

## 12. Correctness Checks

Verify the following identities:

$$
a+0=a
$$

$$
a-a=0
$$

$$
a\cdot0=0
$$

For \(b\ne0\), integer division must satisfy

$$
a=bq+r,\qquad |r|<|b|
$$

The quotient \(q\) is truncated toward zero, and the remainder \(r\) is zero or has the same sign as \(a\).