#include <iostream>
#include <unordered_map>

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

bool is_prime_memo(uint64_t x) {
  static std::unordered_map<uint64_t, bool> prime_map;

  try {
    return prime_map.at(x);
  } catch (std::exception& e) {
    const bool ret = is_prime(x);
    prime_map[x] = ret;
    return ret;
  }
}

void p5(uint64_t x) {
  for (uint64_t i = 2; i < x; ++i) {
    if (is_prime_memo(i) && is_prime_memo(i + 6)) {
      std::cout << i << " " << i + 6 << std::endl;
    }
  }
}

int main() {
  p5(100);

  return 0;
}
