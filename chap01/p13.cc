#include <iostream>

double p13(void) {
  double ret = 1;

  // Wallis' product
  // 2/1 * 2/3 * 4/3 * 4/5 * 6/5 * 6/7 * ... = pi/2
  for (uint32_t i = 1; i < 1000000; ++i) {
    double n = static_cast<double>(i);
    ret *= ((2 * n) / (2 * n - 1)) * ((2 * n) / (2 * n + 1));
  }

  return ret * 2;
}

int main() {
  std::cout << p13() << std::endl;

  return 0;
}
