#include <algorithm>
#include <array>
#include <future>
#include <iostream>
#include <random>

template <class RandomIt>
RandomIt partition(RandomIt first, RandomIt last) {
  auto const pivot = *first;
  auto i = first + 1;
  auto j = last - 1;
  while (i <= j) {
    while (i <= j && *i <= pivot) {
      i++;
    }

    while (i <= j && *j > pivot) {
      j--;
    }

    if (i < j) {
      std::iter_swap(i, j);
    }
  }

  std::iter_swap(i - 1, first);

  return i - 1;
}

template <class RandomIt>
void pquicksort(RandomIt first, RandomIt last) {
  if (first < last) {
    auto const p = partition(first, last);

    if (last - first <= 10000) {
      pquicksort(first, p);
      pquicksort(p + 1, last);
    } else {
      auto f1 = std::async(std::launch::async,
                           [first, p]() { pquicksort(first, p); });
      auto f2 = std::async(std::launch::async,
                           [last, p]() { pquicksort(p + 1, last); });

      f1.wait();
      f2.wait();
    }
  }
}

int main() {
  std::random_device rd;
  std::mt19937 mt;
  auto seed_data = std::array<int, std::mt19937::state_size>{};
  std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
  std::seed_seq seq(std::cbegin(seed_data), std::cend(seed_data));
  mt.seed(seq);
  std::uniform_int_distribution<> ud(1, 1000);

  size_t const count = 10000;
  std::vector<int> data(count);
  std::generate_n(std::begin(data), count, [&mt, &ud]() { return ud(mt); });
  pquicksort(std::begin(data), std::end(data));

  for (auto& x : data) {
    std::cout << x << std::endl;
  }

  return 0;
}
