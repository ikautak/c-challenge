#include <array>
#include <chrono>
#include <execution>
#include <iostream>
#include <numeric>
#include <thread>

int main() {
  std::cout << "hw concurrency " << std::thread::hardware_concurrency()
            << std::endl;

  std::array<uint64_t, 10> data;
  std::iota(std::begin(data), std::end(data), 0);

  std::transform(std::execution::par, std::begin(data), std::end(data),
                 std::begin(data), [](uint64_t x) {
                   std::cout << "hello" << std::endl;
                   std::this_thread::sleep_for(std::chrono::seconds(1));
                   return x * x;
                 });

  for (auto& x : data) {
    std::cout << x << std::endl;
  }

  return 0;
}
