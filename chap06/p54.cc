#include <iostream>
#include <vector>

template <typename T>
std::vector<std::pair<T, T>> make_pair(std::vector<T> in) {
  std::vector<std::pair<T, T>> ret;

  if (in.size() & 1) {
    in.pop_back();
  }

  for (size_t i = 0; i < in.size(); i += 2) {
    ret.push_back({in[i], in[i + 1]});
  }

  return ret;
}

int main() {
  std::vector<int> v{1, 1, 3, 5, 8, 13, 21};
  auto result = make_pair(v);
  for (auto const& [v1, v2] : result) {
    std::cout << '{' << v1 << ',' << v2 << '}' << std::endl;
  }
}
