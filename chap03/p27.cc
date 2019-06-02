#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> split(std::string str, std::string sp) {
  std::vector<std::string> ret;

  std::size_t prev_pos = 0;
  while (1) {
    std::size_t pos = str.find_first_of(sp, prev_pos);
    if (pos == std::string::npos) {
      break;
    }

    ret.push_back(str.substr(prev_pos, pos - prev_pos));
    prev_pos = pos + 1;
  }

  if (prev_pos < str.length()) {
    ret.push_back(str.substr(prev_pos, std::string::npos));
  }

  return ret;
}

int main() {
  auto a = split("this is a sample", " ");
  for (auto&& x : a) {
    std::cout << x << std::endl;
  }

  auto b = split("this,is a.sample!!", ",.! ");
  for (auto&& x : b) {
    std::cout << x << std::endl;
  }

  return 0;
}
