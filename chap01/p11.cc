#include <iostream>
#include <string>
#include <vector>

std::string p11(uint32_t x) {
  static const std::vector<std::pair<uint32_t, std::string>> roman_list = {
      {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"},
      {90, "XC"},  {50, "L"},   {40, "XL"}, {10, "X"},   {9, "IX"},
      {5, "V"},    {4, "IV"},   {1, "I"}};

  std::string ret;

  for (auto&& r : roman_list) {
    while (x >= r.first) {
      ret += r.second;
      x -= r.first;
    }
  }

  return ret;
}

int main() {
  for (uint32_t i = 1; i <= 100; ++i) {
    std::cout << i << " " << p11(i) << std::endl;
  }

  return 0;
}
