#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <thread>
#include <vector>

template <typename Iterator, typename F>
auto pprocess(Iterator begin, Iterator end, F&& f) {
  auto size = std::distance(begin, end);

  int const thread_count = 10;  // std::thread::hardware_concurrency();
  std::vector<std::thread> threads;
  std::vector<typename std::iterator_traits<Iterator>::value_type> mins(
      thread_count);

  auto first = begin;
  auto last = first;
  size /= thread_count;

  for (int i = 0; i < thread_count; ++i) {
    first = last;
    if (i == thread_count - 1) {
      last = end;
    } else {
      std::advance(last, size);
    }

    threads.emplace_back([first, last, &f, &r = mins[i]]() {
      r = std::forward<F>(f)(first, last);
    });
  }

  for (auto& t : threads) {
    t.join();
  }

  return std::forward<F>(f)(std::begin(mins), std::end(mins));
}

template <typename Iterator>
auto pmin(Iterator begin, Iterator end) {
  return pprocess(begin, end,
                  [](auto b, auto e) { return *std::min_element(b, e); });
}

template <typename Iterator>
auto pmax(Iterator begin, Iterator end) {
  return pprocess(begin, end,
                  [](auto b, auto e) { return *std::max_element(b, e); });
}

int main() {
  const size_t count = 1000;

  std::vector<int> data(count);
  std::iota(std::begin(data), std::end(data), 0);

  auto rmin = pmin(std::cbegin(data), std::cend(data));
  auto rmax = pmax(std::cbegin(data), std::cend(data));

  std::cout << rmin << std::endl;
  std::cout << rmax << std::endl;

  return 0;
}
