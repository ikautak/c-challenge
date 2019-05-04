#include <cmath>
#include <iostream>

void p9(uint64_t x) {
  const uint64_t root = static_cast<uint64_t>(std::sqrt(x));

  while (x % 2 == 0) {
    x /= 2;
    std::cout << 2 << " ";
  }

  for (uint64_t i = 3; i < root; i += 2) {
    while (x % i == 0) {
      x /= i;
      std::cout << i << " ";
    }
  }

  if (x > 2) {
    std::cout << x;
  }

  std::cout << std::endl;
}

int main() {
  p9(600);
  p9(851);
  p9(475);
  p9(143);

  return 0;
}
