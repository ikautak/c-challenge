#include <iomanip>
#include <iostream>

template <typename T>
void print_hex_str(std::initializer_list<T> list) {
  for (auto& x : list) {
    std::cout << std::setw(2) << std::setfill('0') << std::hex << x;
  }
  std::cout << std::endl;
}

int main() {
  print_hex_str({0xBA, 0xAD, 0xF0, 0x0D});
  print_hex_str({1, 2, 3, 4, 5, 6});

  return 0;
}
