#ifndef ARB_H
#define ARB_H

#include <cstddef>
#include <cstdio>
#include <random>
#include <vector>

struct BigInt {
public:
  // Constructor
  BigInt(): index{0}, sign{1} {};
  explicit BigInt(long long num) : index(), sign(1) {
    unsigned long long value;
    if (num < 0) {
      sign = -1;
      value = static_cast<unsigned long long>(-(num + 1)) + 1;
    } else {
      value = static_cast<unsigned long long>(num);
    }
    do {
      index.push_back(static_cast<int>(value % 10));
      value /= 10;
    } while(value > 0);

    normalize();
  };

  BigInt randomize(std::size_t length);

  friend std::ostream& operator<<(std::ostream& os, const BigInt& num);
  
  BigInt operator+(const BigInt& other) const;
  BigInt operator-(const BigInt& other) const;
  BigInt operator*(const BigInt& other) const;
  BigInt operator/(const BigInt& other) const;
  
  bool operator>(const BigInt& other) const;
  bool operator==(const BigInt& other) const;
  bool operator<(const BigInt& other) const;

private:
  std::vector<int> index;
  int sign;

  // Arithmetic functions
  BigInt add(const BigInt& other) const;
  BigInt sub(const BigInt& other) const;
  BigInt mult(const BigInt& other) const;
  BigInt div(const BigInt& other) const;

  
  BigInt add_abs(const BigInt& other) const;
  BigInt sub_abs(const BigInt& other) const;
  int compare_abs(const BigInt& a, const BigInt& b) const;

  void normalize();
};

inline BigInt BigInt::randomize(std::size_t length)
{
  static bool seed = false;

  if (!seed) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    seed = true;
  }

  BigInt result;
  result.index.resize(length);

  for (std::size_t i = 0; i < length; i++) {
    result.index[i] = std::rand() % 10;
  }

  result.index.back() = 1 + std::rand() % 9;
  
  result.sign = (std::rand() % 2 == 0) ? 1 : -1;
  return result;
}

inline std::ostream& operator<<(std::ostream& os, const BigInt& num)
{
  if (num.sign < 0) {
    os << '-';
  }

  for (std::size_t i = num.index.size(); i > 0; --i) {
    os << num.index[i - 1];
  }

  return os;
}

inline void BigInt::normalize()
{
  while (index.size() > 1 && index.back() == 0) {
    index.pop_back();
  }
  if (index.empty()) {
    index.push_back(0);
  }
  if (index.size() == 1 && index[0] == 0) {
    sign = 1;
  }
}

// Operator Overloading
inline BigInt BigInt::operator+(const BigInt &other) const 
{
  return add(other);
}

inline BigInt BigInt::operator-(const BigInt &other) const 
{
  return sub(other);
}

inline BigInt BigInt::operator*(const BigInt &other) const 
{
  return mult(other);
}

inline BigInt BigInt::operator/(const BigInt &other) const 
{
  return div(other);
}

inline BigInt BigInt::add_abs(const BigInt& other) const
{
  BigInt result;
  result.index.clear();
  int carry = 0;
  std::size_t length = std::max(index.size(), other.index.size());

  for (std::size_t i = 0; i < length || carry; i++) {
    int a_val = (i < index.size()) ? index[i] : 0,
        b_val = (i < other.index.size()) ? other.index[i] : 0;

    int sum = a_val + b_val + carry;
    result.index.push_back(sum % 10);
    carry = sum / 10;
  }
  result.normalize();
  return result;
}

// Assume |this| >= |other|
inline BigInt BigInt::sub_abs(const BigInt& other) const
{
  BigInt result;
  result.index.clear();
  int borrow = 0;

  for (std::size_t i = 0; i < index.size(); i++) {
    int a_val = (i < index.size()) ? index[i] : 0,
        b_val = (i < other.index.size()) ? other.index[i] : 0;

    int diff = a_val - b_val - borrow;
    if (diff < 0) {
      diff += 10;
      borrow = 1;
    } else {
      borrow = 0;
    }

    result.index.push_back(diff);
  }

  result.normalize();
  return result;
}

inline int BigInt::compare_abs(const BigInt&a, const BigInt&b) const
{
  if (a.index.size() != b.index.size()) {
    return (a.index.size() > b.index.size()) ? 1 : -1;
  }

  for (std::size_t i = a.index.size(); i > 0; i--) {
    if (a.index[i - 1] != b.index[i - 1]) {
      return (a.index[i - 1] > b.index[i - 1]) ? 1 : -1;
    }
  }

  return 0;
}

inline BigInt BigInt::add(const BigInt& other) const
{
  BigInt result;
  int cmp = compare_abs(*this, other);

  if (sign == other.sign) {
    result = add_abs(other);
    result.sign = sign;
  } else if (cmp == 0) {
    return BigInt();
  } else if (cmp > 0) {
    result = sub_abs(other);
    result.sign = sign;
  } else {
    result = other.sub_abs(*this);
    result.sign = other.sign;
  }

  result.normalize();
  return result;
}

inline BigInt BigInt::sub(const BigInt& other) const
{
  BigInt negated = other;
  negated.sign *= -1;
  negated.normalize();
  return add(negated);
}

inline BigInt BigInt::mult(const BigInt& other) const
{
  BigInt result;
  result.index.assign(index.size() + other.index.size(), 0);

  for (std::size_t i = 0; i < index.size(); i++) {
    int carry = 0;
    for (std::size_t j = 0; j < other.index.size() || carry; j++) {
      long long cur = result.index[i + j] + carry;

      if (j < other.index.size()) {
        cur += 1LL * index[i] * other.index[j];
      }
      result.index[i + j] = static_cast<int>(cur % 10);
      carry = static_cast<int>(cur / 10);
    }
  }

  result.sign = sign * other.sign;
  result.normalize();
  return result;
}

inline BigInt BigInt::div(const BigInt& other) const
{
  BigInt dividend = *this;
  BigInt divisor = other;

  dividend.sign = 1;
  divisor.sign = 1;

  if (compare_abs(dividend, divisor) < 0) {
    return BigInt();
  }

  BigInt quotient;
  quotient.index.assign(index.size(), 0);

  BigInt remainder;
  for (std::size_t i = index.size(); i > 0; i--) {
    remainder.index.insert(remainder.index.begin(), index[i - 1]);
    remainder.normalize();

    int digit = 0;

    while (compare_abs(remainder, divisor) >= 0) {
      remainder = remainder.sub_abs(divisor);
      ++digit;
    }
    quotient.index[i - 1] = digit;
  }
  quotient.sign = sign * other.sign;
  quotient.normalize();
  return quotient;
}

inline bool BigInt::operator>(const BigInt& other) const
{
  if (sign != other.sign) {
    return sign > other.sign;
  }

  int cmp = compare_abs(*this, other);

  if (sign > 0) {
    return cmp > 0;
  }
  return cmp < 0;
}

inline bool BigInt::operator==(const BigInt& other) const
{
  return (sign == other.sign) && compare_abs(*this, other) == 0;
}

inline bool BigInt::operator<(const BigInt& other) const
{
  if (sign != other.sign) {
    return sign < other.sign;
  }

  int cmp = compare_abs(*this, other);

  if (sign > 0) {
    return cmp < 0;
  }
  return cmp > 0;
}
#endif