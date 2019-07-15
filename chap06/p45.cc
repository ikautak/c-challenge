#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

template <class T,
          class Compare = std::less<typename std::vector<T>::value_type>>
class priority_queue {
  using value_type = typename std::vector<T>::value_type;
  using size_type = typename std::vector<T>::size_type;
  using refrence = typename std::vector<T>::reference;
  using const_reference = typename std::vector<T>::const_reference;

 public:
  bool empty() const noexcept { return data_.empty(); }
  size_type size() const noexcept { return data_.size(); }

  void push(value_type const& value) {
    data_.push_back(value);
    std::push_heap(std::begin(data_), std::end(data_), compare_);
  }

  void pop() {
    std::pop_heap(std::begin(data_), std::end(data_), compare_);
    data_.pop_back();
  }

  const_reference top() const { return data_.front(); }
  void swap(priority_queue& other) noexcept {
    swap(data_, other.data_);
    swap(compare_, other.compare_);
  }

 private:
  std::vector<T> data_;
  Compare compare_;
};

template <class T, class Compare>
void swap(priority_queue<T, Compare>& lhs,
          priority_queue<T, Compare>& rhs) noexcept(noexcept(lhs.swap(rhs))) {
  lhs.swap(rhs);
}

int main() {
  priority_queue<int> q;

  for (int i : {1, 5, 3, 1, 13, 21, 8}) {
    q.push(i);
  }

  assert(!q.empty());
  assert(q.size() == 7);

  while (!q.empty()) {
    std::cout << q.top() << ' ';
    q.pop();
  }
  std::cout << std::endl;

  return 0;
}
