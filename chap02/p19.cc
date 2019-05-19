#include <iostream>
#include <iterator>
#include <list>
#include <vector>

template <typename T, typename... Args>
void push_back(T& t, Args&&... args) {
  (t.push_back(args), ...);
}

int main() {
  std::vector<int> v;
  push_back(v, 1, 2, 3, 4);
  std::copy(std::cbegin(v), std::cend(v),
            std::ostream_iterator<int>(std::cout, " "));

  std::list<int> l;
  push_back(l, 5, 6, 7, 8);
  std::copy(std::cbegin(l), std::cend(l),
            std::ostream_iterator<int>(std::cout, " "));

  return 0;
}
