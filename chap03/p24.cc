#include <iomanip>
#include <iostream>

void print_bin_str(std::string in, bool _0x = false) {
  const auto len = in.length();

  std::cout << "{ ";

  for (size_t i = 0; i < len; i += 2) {
    if (i != 0) {
      std::cout << ',';
    }

    std::cout << " ";

    if (_0x) {
      std::cout << "0x" << std::uppercase << std::hex << std::setw(2)
                << std::setfill('0');
    }

    std::cout << std::stoi(in.substr(i, 2), nullptr, 16);
  }

  std::cout << " }" << std::endl;
}

int main() {
  print_bin_str("BAADF00D", true);
  print_bin_str("010203040506");

  return 0;
}
