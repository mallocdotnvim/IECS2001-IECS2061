#include <cstdio>
#include <iostream>
#include "arbitrary-precision.hpp"

int main(void)
{
  BigInt a, b;
  a = a.randomize(100), b = b.randomize(100);
  
  std::cout << "a = " << a << '\n' << "b = " << b << '\n';
  std::cout << "a + b = " << a + b << '\n';
  std::cout << "a - b = " << a - b << '\n';
  std::cout << "a * b = " << a * b << '\n';
  std::cout << "a / b = " << a / b << '\n';
  std::cout << "a > b = " << (a > b) << '\n';
  std::cout << "a < b = " << (a < b) << '\n';
  return 0;
}