#include <iostream>
#include <map>
#include <vector>

template <typename T>
std::vector<std::pair<T, size_t>> find_most_frequent(
    std::vector<T> const& range) {
  std::map<T, size_t> counts;

  size_t max = 0;
  for (auto& e : range) {
    // Count
    counts[e] += 1;

    // Save max value
    max = std::max(max, counts[e]);
  }

  std::vector<std::pair<T, size_t>> result;
  for (auto& e : counts) {
    if (e.second == max) {
      result.push_back(e);
    }
  }
  // std::cout << result.size() << std::endl;

  return result;
}

int main() {
  auto range = std::vector<int>{1, 1, 3, 5, 8, 13, 3, 5, 8, 8, 5};

  auto result = find_most_frequent(range);

  for (auto& [e, count] : result) {
    std::cout << e << " : " << count << std::endl;
  }

  return 0;
}
