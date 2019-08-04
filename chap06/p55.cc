#include <iostream>
#include <vector>

template <typename T, typename U>
std::vector<std::pair<T, U>> zip(std::vector<T> a, std::vector<U> b) {
  std::vector<std::pair<T, U>> ret;
  const auto count = std::min(a.size(), b.size());

  for (size_t i = 0; i < count; ++i) {
    ret.push_back({a[i], b[i]});
  }

  return ret;
}

int main() {
  std::vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<int> v2{1, 1, 3, 5, 8, 13, 21};
  auto result = zip(v1, v2);
  for (auto const& [v1, v2] : result) {
    std::cout << '{' << v1 << ',' << v2 << '}' << std::endl;
  }
}
