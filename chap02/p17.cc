#include <iostream>
#include <iterator>
#include <vector>

template <class T>
class array2d {
 public:
  explicit array2d(std::initializer_list<std::initializer_list<T>> l) {
    std::vector<std::initializer_list<T>> init_vec = l;

    for (auto& init : init_vec) {
      data_.push_back(init);
    }
  }
  size_t get_w(void) const {
    if (data_.empty()) {
      return 0;
    } else {
      return data_[0].size();
    }
  }
  size_t get_h(void) const { return data_.size(); }

  T& operator()(int h, int w) { return data_[h][w]; }

  void fill(T t) {
    for (auto& array : data_) {
      for (auto& x : array) {
        x = t;
      }
    }
  }

  void swap(array2d& other) {
    for (size_t i = 0; i < data_.size(); ++i) {
      data_[i].swap(other.data_[i]);
    }
  }

  void print(void) const {
    for (auto& array : data_) {
      for (auto& x : array) {
        std::cout << x << " ";
      }
      std::cout << std::endl;
    }
  }

 private:
  std::vector<std::vector<T>> data_;
};

int main() {
  array2d<int> a{{1, 2, 3}, {4, 5, 6}};
  a.print();
  for (size_t i = 0; i < a.get_h(); ++i) {
    for (size_t j = 0; j < a.get_w(); ++j) {
      a(i, j) *= 2;
    }
  }
  a.print();

  // TODO
  //  std::copy(std::cbegin(a), std::cend(a),
  //            std::ostream_iterator<int>(std::cout << " "));

  array2d<int> b{{2, 2}, {2, 2}};
  b.fill(1);
  b.print();

  a.swap(b);
  a.print();

  array2d<int> c(std::move(b));
  c.print();

  return 0;
}
