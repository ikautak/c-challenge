#include <iostream>
#include <string>
#include <vector>

void p12(void) {
  std::vector<uint32_t> step_memo(1000000, 0);
  uint32_t max_step = 0;
  uint32_t max_n = 0;

  for (uint32_t i = 2; i < 1000000; ++i) {
    uint32_t step = 0;
    uint32_t x = i;
    // std::cout << x << " start" << std::endl;

    while (x != 1 && x >= i) {
      if (x & 0x1) {
        x = x * 3 + 1;
      } else {
        x /= 2;
      }

      ++step;
      // std::cout << x << std::endl;
    }

    step_memo[i] = step + step_memo[x];
    // std::cout << "step " << step_memo[i] << std::endl;

    if (max_step < step_memo[i]) {
      max_step = step_memo[i];
      max_n = x;
    }

    // std::string in;
    // std::cin >> in;
  }

  std::cout << max_n << " " << max_step << std::endl;
}

int main() {
  p12();

  return 0;
}
