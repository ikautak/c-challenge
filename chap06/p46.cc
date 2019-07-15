#include <cassert>
#include <iostream>
#include <vector>

template <class T>
class circular_buffer_iterator;

template <class T>
class circular_buffer {
  using const_iterator = circular_buffer_iterator<T>;

 public:
  circular_buffer() = delete;
  explicit circular_buffer(size_t const size) : data_(size) {}

  void clear() noexcept {
    head_ = -1;
    size_ = 0;
  }

  bool empty() const noexcept { return size_ == 0; }
  bool full() const noexcept { return size_ == data_.size(); }
  size_t capacity() const noexcept { return data_.size(); }
  size_t size() const noexcept { return size_; }

  void push(T const x) {
    head_ = next_pos();
    std::cout << "push " << head_ << std::endl;
    data_[head_] = x;

    if (size_ < data_.size()) {
      size_++;
    }
  }

  T pop() {
    if (empty()) {
      throw std::runtime_error("empty buffer");
    }

    auto pos = first_pos();
    std::cout << "pop " << pos << std::endl;
    size_--;
    return data_[pos];
  }

  const_iterator begin() const {
    return const_iterator(*this, first_pos(), empty());
  }
  const_iterator end() const { return const_iterator(*this, next_pos(), true); }

 private:
  std::vector<T> data_;
  size_t head_ = -1;
  size_t size_ = 0;

  size_t next_pos() const noexcept {
    return (size_ == 0) ? 0 : ((head_ + 1) % data_.size());
  }
  size_t first_pos() const noexcept {
    return (size_ == 0) ? 0
                        : ((head_ + data_.size() - size_ + 1) % data_.size());
  }

  friend class circular_buffer_iterator<T>;
};

template <class T>
class circular_buffer_iterator {
  using self_type = circular_buffer_iterator;
  using value_type = T;
  using reference = T &;
  using const_reference = T const &;
  using pointer = T *;
  using const_pointer = T const *;
  using iterator_category = std::random_access_iterator_tag;
  using difference_type = ptrdiff_t;

 public:
  circular_buffer_iterator(circular_buffer<T> const &buf, size_t const pos,
                           bool const last)
      : buffer_(buf), index_(pos), last_(last) {}

  self_type &operator++() {
    if (last_) {
      throw std::out_of_range(
          "Iterator cannot be incremented past the end of range.");
    }

    index_ = (index_ + 1) % buffer_.data_.size();
    last_ = index_ == buffer_.next_pos();
    return *this;
  }

  self_type operator++(int) {
    self_type tmp = *this;
    ++(*this);
    return tmp;
  }

  bool operator==(self_type const &other) const {
    assert(compatible(other));
    return index_ == other.index_ && last_ == other.last_;
  }

  bool operator!=(self_type const &other) const { return !(*this == other); }

  const_reference operator*() const { return buffer_.data_[index_]; }
  const_pointer operator->() const { return std::addressof(operator*()); }

 private:
  bool compatible(self_type const &other) const {
    return &buffer_ == &other.buffer_;
  }

  circular_buffer<T> const &buffer_;
  size_t index_ = 0;
  bool last_ = false;
};

template <typename T>
void print(circular_buffer<T> &buf) {
  for (auto &e : buf) {
    std::cout << e << ' ';
  }

  std::cout << std::endl;
}

int main() {
  circular_buffer<int> cbuf(5);
  assert(cbuf.empty());
  assert(!cbuf.full());
  assert(cbuf.size() == 0);
  print(cbuf);

  cbuf.push(1);
  cbuf.push(2);
  cbuf.push(3);
  assert(!cbuf.empty());
  assert(!cbuf.full());
  assert(cbuf.size() == 3);
  print(cbuf);

  auto item = cbuf.pop();
  assert(item == 1);
  assert(!cbuf.empty());
  assert(!cbuf.full());
  assert(cbuf.size() == 2);

  cbuf.push(4);
  cbuf.push(5);
  cbuf.push(6);
  assert(!cbuf.empty());
  assert(cbuf.full());
  assert(cbuf.size() == 5);
  print(cbuf);

  cbuf.push(7);
  cbuf.push(8);
  assert(!cbuf.empty());
  assert(cbuf.full());
  assert(cbuf.size() == 5);
  print(cbuf);

  item = cbuf.pop();
  assert(item == 4);
  item = cbuf.pop();
  assert(item == 5);
  item = cbuf.pop();
  assert(item == 6);

  assert(!cbuf.empty());
  assert(!cbuf.full());
  assert(cbuf.size() == 2);
  print(cbuf);

  item = cbuf.pop();
  assert(item == 7);
  item = cbuf.pop();
  assert(item == 8);

  assert(cbuf.empty());
  assert(!cbuf.full());
  assert(cbuf.size() == 0);
  print(cbuf);

  cbuf.push(9);
  assert(!cbuf.empty());
  assert(!cbuf.full());
  assert(cbuf.size() == 1);
  print(cbuf);

  return 0;
}
