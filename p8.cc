#include <iostream>

void p8(void) {
  for (uint32_t a = 1; a <= 9; ++a) {
    for (uint32_t b = 0; b <= 9; ++b) {
      for (uint32_t c = 0; c <= 9; ++c) {
        uint64_t x = a * 100 + b * 10 + c;
        uint64_t as = a * a * a + b * b * b + c * c * c;
        if (x == as) {
          std::cout << a << " " << b << " " << c << std::endl;
        }
      }
    }
  }
}

int main() {
  p8();
  return 0;
}
