#include <iostream>
#include <numeric>

constexpr uint64_t p2(uint64_t a, uint64_t b) { return std::gcd(a, b); }

int main() {
  std::cout << p2(12, 9) << std::endl;

  return 0;
}
