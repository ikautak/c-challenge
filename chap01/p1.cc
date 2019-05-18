#include <iostream>

constexpr uint64_t p1(uint64_t x) {
  uint64_t sum = 0;

  for (uint64_t i = 1; i < x; i++) {
    if (((i % 3) == 0) || ((i % 5) == 0)) {
      sum += i;
    }
  }

  return sum;
}

int main() {
  std::cout << p1(100) << std::endl;

  return 0;
}
