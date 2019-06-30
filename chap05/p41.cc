#include <iostream>

#include "date.h"
#include "iso_week.h"

uint32_t week_day(const int y, const uint32_t m, const uint32_t d) {
  using namespace date;

  if (m < 1 || m > 12 || d < 1 || d > 31) {
    return 0;
  }

  const auto dt = date::year_month_day{year{y}, month{m}, day{d}};
  const auto tiso = iso_week::year_weeknum_weekday{dt};

  return static_cast<uint32_t>(tiso.weekday());
}

int main() {
  auto wday = week_day(2019, 6, 30);
  std::cout << wday << std::endl;

  return 0;
}
