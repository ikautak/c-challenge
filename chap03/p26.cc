#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
std::string join(T& str, std::string sp) {
  std::string ret;

  bool first = true;
  for (auto&& x : str) {
    if (first) {
      first = false;
    } else {
      ret += sp;
    }

    ret += x;
  }

  return ret;
}

int main() {
  std::vector<std::string> a{"aaa", "bbb", "ccc"};
  std::vector<std::string> b{"asdf"};
  std::vector<std::string> c{""};

  std::cout << join(a, ",") << std::endl;
  std::cout << join(b, " ") << std::endl;
  std::cout << join(c, "   ") << std::endl;

  return 0;
}
