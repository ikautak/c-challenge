#include <iostream>
#include <numeric>

constexpr uint64_t p3(uint64_t a, uint64_t b) { return a * b / std::gcd(a, b); }

int main() {
  std::cout << p3(12, 11) << std::endl;
  return 0;
}
