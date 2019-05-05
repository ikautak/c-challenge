#include <iostream>
#include <string>

bool p14(std::string isbn) {
  if (isbn.length() != 10) {
    return false;
  }

  int check_digit = isbn[9] - '0';
  isbn.erase(9);

  int w = 10;
  int sum = 0;
  for (auto& c : isbn) {
    sum += w * (c - '0');
    --w;
  }

  return check_digit == (11 - (sum % 11));
}

int main() {
  std::cout << p14("4764902222") << std::endl;
  std::cout << p14("3764902222") << std::endl;

  return 0;
}
