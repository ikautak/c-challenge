#include <algorithm>
#include <future>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

template <typename Iterator, typename F>
auto pprocess(Iterator begin, Iterator end, F&& f) {
  auto size = std::distance(begin, end);

  int const task_count = 10;  // std::thread::hardware_concurrency();
  std::vector<std::future<typename std::iterator_traits<Iterator>::value_type>>
      tasks;

  auto first = begin;
  auto last = first;
  size /= task_count;

  for (int i = 0; i < task_count; ++i) {
    first = last;
    if (i == task_count - 1) {
      last = end;
    } else {
      std::advance(last, size);
    }

    tasks.emplace_back(std::async(std::launch::async, [first, last, &f]() {
      return std::forward<F>(f)(first, last);
    }));
  }

  std::vector<typename std::iterator_traits<Iterator>::value_type> mins;
  for (auto& x : tasks) {
    mins.push_back(x.get());
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
