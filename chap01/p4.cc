#include <iostream>

bool is_prime(const uint64_t x) {
  if (x <= 1) {
    // 0 or 1
    return false;
  }

  if (x <= 3) {
    // 2 or 3
    return true;
  }

  if ((x % 2) == 0) {
    return false;
  }

  if ((x % 3) == 0) {
    return false;
  }

  const uint64_t mod6 = x % 6;
  if ((mod6 != 1) && (mod6 != 5)) {
    // 0, 2, 3, 4
    return false;
  }

  for (uint64_t i = 5; i * i <= x; i += 6) {
    if ((x % i) == 0) {
      // 6n - 1
      return false;
    }

    if ((x % (i + 2)) == 0) {
      // 6n + 1
      return false;
    }
  }

  return true;
}

uint64_t p4(uint64_t x) {
  for (uint64_t i = x - 1; i > 1; --i) {
    if (is_prime(i)) {
      return i;
    }
  }

  return 0;
}

int main() {
  std::cout << p4(100) << std::endl;

  return 0;
}
