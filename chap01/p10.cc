#include <bitset>
#include <iostream>

uint32_t gray_encode(uint32_t x) { return x ^ (x >> 1); }

uint32_t gray_decode(uint32_t x) {
  for (uint32_t bit = 1u << 31; bit > 1; bit >>= 1) {
    if (x & bit) {
      x ^= bit >> 1;
    }
  }

  return x;
}

std::string to_binary(uint32_t x, uint32_t digits) {
  return std::bitset<32>(x).to_string().substr(32 - digits, digits);
}

int main() {
  for (uint32_t n = 0; n < 32; ++n) {
    const uint32_t enc = gray_encode(n);
    const uint32_t dec = gray_decode(enc);

    std::cout << n << "\t" << to_binary(n, 5) << "\t" << to_binary(enc, 5)
              << "\t" << dec << std::endl;
  }

  return 0;
}
