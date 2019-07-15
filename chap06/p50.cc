#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> filter_numbers(std::vector<std::string>& numbers,
                                        std::string const& code) {
  // asdfad
  // asdfad
  std::vector<std::string> result;

  for (auto& n : numbers) {
    if ((n.find(code) == 0) || (n.find("+" + code) == 0)) {
      result.push_back(n);
    }
  }

  return result;
}

int main() {
  std::vector<std::string> numbers{"+40744909080", "44 7520 112233",
                                   "+44 7555 123456", "40 7200 123456",
                                   "7555 123456"};

  auto result = filter_numbers(numbers, "44");

  for (auto& x : result) {
    std::cout << x << std::endl;
  }

  return 0;
}
