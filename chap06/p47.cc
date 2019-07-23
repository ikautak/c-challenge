#include <iostream>
#include <iterator>
#include <mutex>
#include <numeric>
#include <thread>
#include <vector>

template <typename T>
class double_buffer {
  using value_type = T;
  using reference = T &;
  using const_reference = T const &;
  using pointer = T *;

 public:
  explicit double_buffer(size_t const size) : rbuf(size), wbuf(size) {}

  size_t size() const noexcept { return rbuf.size(); }

  void write(T const *const ptr, size_t const size) {
    std::unique_lock<std::mutex> lock(mt);
    auto length = std::min(size, wbuf.size());
    std::copy(ptr, ptr + length, std::begin(wbuf));
    wbuf.swap(rbuf);
  }

  template <class Output>
  void read(Output it) const {
    std::unique_lock<std::mutex> lock(mt);
    std::copy(std::cbegin(rbuf), std::cend(rbuf), it);
  }

  pointer data() const {
    std::unique_lock<std::mutex> lock(mt);
    return rbuf.data();
  }

  reference operator[](size_t const pos) {
    std::unique_lock<std::mutex> lock(mt);
    return rbuf[pos];
  }

  const_reference operator[](size_t const pos) const {
    std::unique_lock<std::mutex> lock(mt);
    return rbuf[pos];
  }

  void swap(double_buffer other) {
    std::swap(rbuf, other.rbuf);
    std::swap(wbuf, other.wbuf);
  }

 private:
  std::vector<T> rbuf;
  std::vector<T> wbuf;
  mutable std::mutex mt;
};

template <typename T>
void print_buffer(double_buffer<T> const &buf) {
  buf.read(std::ostream_iterator<T>(std::cout, " "));
  std::cout << std::endl;
}

int main() {
  double_buffer<int> buf(10);

  std::thread t([&buf]() {
    for (int i = 1; i < 1000; i += 10) {
      int data[10] = {};
      std::iota(std::begin(data), std::end(data), i);
      buf.write(data, std::size(data));

      using namespace std::chrono_literals;
      std::this_thread::sleep_for(100ms);
    }
  });

  auto start = std::chrono::system_clock::now();
  do {
    print_buffer(buf);

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(150ms);

  } while (std::chrono::duration_cast<std::chrono::seconds>(
               std::chrono::system_clock::now() - start)
               .count() < 12);

  t.join();

  return 0;
}
