#include <iostream>
#include <string>
#include <vector>

void normalize_phone_numbers(std::vector<std::string>& numbers,
                             std::string const& code) {
  // asdf
  for (auto& n : numbers) {
    if (n.find("+" + code) == 0) {
      // Do nothing.
    } else if (n.find(code) == 0) {
      n = "+" + n;
    } else if (n[0] == '0') {
      n = "+" + code + n.substr(1);
    } else {
      n = "+" + code + n;
    }

    std::string x;
    for (auto& c : n) {
      if (!std::isspace(c)) {
        x += c;
      }
    }

    n = x;
  }
}

int main() {
  std::vector<std::string> numbers{"07555 123456", "07555123456",
                                   "+44 7555 123456", "44 7555 123456",
                                   "7555 123456"};

  normalize_phone_numbers(numbers, "44");

  for (auto const& number : numbers) {
    std::cout << number << std::endl;
  }

  return 0;
}
