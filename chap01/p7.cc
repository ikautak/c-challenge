#include <cmath>
#include <iostream>
#include <unordered_map>

uint64_t sum_div(uint64_t x) {
  uint64_t ret = 1;
  const uint64_t root = static_cast<uint64_t>(std::sqrt(x));

  for (uint64_t i = 2; i <= root; ++i) {
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

uint64_t sum_div_memo(uint64_t x) {
  static std::unordered_map<uint64_t, uint64_t> sum_div_map;

  try {
    return sum_div_map.at(x);
  } catch (std::exception& e) {
    const uint64_t ret = sum_div(x);
    sum_div_map[x] = ret;
    return ret;
  }
}

int main() {
  for (uint64_t i = 2; i < 1000; ++i) {
    uint64_t sum1 = sum_div_memo(i);
    if (sum1 == i) {
      continue;
    }

    uint64_t sum2 = sum_div_memo(sum1);
    if (i == sum2) {
      std::cout << i << ',' << sum1 << std::endl;
    }
  }

  return 0;
}
