#include <iostream>

#include "date.h"

inline int number_of_days(int const y1, uint32_t const m1, uint32_t d1, int y2,
                          uint32_t m2, uint32_t d2) {
  using namespace date;

  return (sys_days{year{y1} / month{m1} / day{d1}} -
          sys_days{year{y2} / month{m2} / day{d2}})
      .count();
}

inline int number_of_days(const date::sys_days& first,
                          const date::sys_days& last) {
  return (last - first).count();
}

int main() {
  auto diff1 = number_of_days(2016, 9, 23, 2017, 5, 15);
  std::cout << diff1 << std::endl;

  using namespace date::literals;
  auto diff2 = number_of_days(2016_y / sep / 23, 15_d / may / 2017);
  std::cout << diff2 << std::endl;

  return 0;
}
