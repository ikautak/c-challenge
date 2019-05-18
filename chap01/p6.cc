#include <cmath>
#include <iostream>

uint64_t sum_div(uint64_t x) {
  uint64_t ret = 1;
  const uint64_t root = static_cast<uint64_t>(std::sqrt(x));

  for (uint64_t i = 2; i < root; ++i) {
    if ((x % i) == 0) {
      const uint64_t d = x / i;

      if (i == d) {
        ret += i;
      } else {
        ret += i + d;
      }
    }
  }

  return ret;
}

void p6(uint64_t x) {
  for (uint64_t n = x; n >= 5; --n) {
    const uint64_t y = sum_div(n);
    if (y > n) {
      std::cout << n << " " << y << " " << y - n << std::endl;
    }
  }
}

int main() {
  p6(1000);

  // std::cout << sum_div(220) << std::endl;
  // std::cout << sum_div(284) << std::endl;

  return 0;
}
