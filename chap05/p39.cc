#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

template <typename Time = std::chrono::microseconds,
          typename Clock = std::chrono::high_resolution_clock>
class perf_timer {
 public:
  template <typename F, typename... Args>
  static Time duration(F&& f, Args... args) {
    auto start = Clock::now();
    std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
    auto end = Clock::now();

    return std::chrono::duration_cast<Time>(end - start);
  }
};

using namespace std::chrono_literals;

void f() { std::this_thread::sleep_for(2s); }
void g(int const /*a*/, int const /*b*/) { std::this_thread::sleep_for(1s); }

int main() {
  auto t1 = perf_timer<std::chrono::microseconds>::duration(f);
  auto t2 = perf_timer<std::chrono::milliseconds>::duration(g, 1, 2);

  std::cout << std::chrono::duration<double, std::nano>(t1 + t2).count()
            << std::endl;
  return 0;
}
