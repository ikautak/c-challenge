#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <list>
#include <vector>

template <class C, class T>
bool contains(C const& c, T const& value) {
  return std::cend(c) != std::find(std::cbegin(c), std::cend(c), value);
}

template <class C, class... T>
bool contains_any(C const& c, T&&... value) {
  return (... || contains(c, value));
}

template <class C, class... T>
bool contains_all(C const& c, T&&... value) {
  return (... && contains(c, value));
}

template <class C, class... T>
bool contains_none(C const& c, T&&... value) {
  return !contains_any(c, std::forward<T>(value)...);
}

int main() {
  std::vector<int> v{1, 2, 3, 4, 5, 6};
  assert(contains_any(v, 0, 3, 30));

  std::array<int, 6> a{{1, 2, 3, 4, 5, 6}};
  assert(contains_all(a, 1, 3, 5, 6));

  std::list<int> l{1, 2, 3, 4, 5, 6};
  assert(!contains_none(l, 0, 6));

  return 0;
}