#include <iostream>

template <typename T>
T my_min(T a, T b) {
  return a < b ? a : b;
}

template <typename T, typename... Ts>
T my_min(T a, Ts... args) {
  return my_min(a, my_min(args...));
}

template <class Compare, typename T>
T my_min_comp(Compare comp, T a, T b) {
  return comp(a, b) ? a : b;
}

template <class Compare, typename T, typename... Ts>
T my_min_comp(Compare comp, T a, Ts... args) {
  return my_min_comp(comp, a, my_min_comp(comp, args...));
}

int main() {
  auto x = my_min(4, 5, 6, 8, 3, 9);
  std::cout << x << std::endl;

  auto y = my_min_comp(std::less<>(), 3, 2, 1, 6);
  std::cout << y << std::endl;

  return 0;
}
