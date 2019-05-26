#include <iomanip>
#include <iostream>

std::string capitalize(std::string in) {
  std::string ret;
  bool search_next_word = true;

  for (auto& c : in) {
    if (c == ' ') {
      ret += ' ';
      search_next_word = true;
    } else {
      if (search_next_word) {
        ret += std::toupper(c);
        search_next_word = false;
      } else {
        ret += std::tolower(c);
      }
    }
  }

  return ret;
}

int main() {
  std::cout << capitalize("the c++ challanger") << std::endl;
  std::cout << capitalize("THE CPP CHALLENGER") << std::endl;

  return 0;
}
