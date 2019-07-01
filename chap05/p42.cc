#include <iostream>

#include "date.h"
#include "iso_week.h"

int day_of_year(const int y, const uint32_t m, const uint32_t d) {
  using namespace date;

  if (m < 1 || m > 12 || d < 1 || d > 31) {
    return 0;
  }

  return (sys_days{year{y} / month{m} / day{d}} - sys_days{year{y} / jan / 0})
      .count();
}

uint32_t calendar_week(const int y, const uint32_t m, const uint32_t d) {
  using namespace date;

  if (m < 1 || m > 12 || d < 1 || d > 31) {
    return 0;
  }

  const auto dt = date::year_month_day{year{y}, month{m}, day{d}};
  const auto tiso = iso_week::year_weeknum_weekday{dt};

  return static_cast<uint32_t>(tiso.weeknum());
}

int main() {
  int y = 2019;
  uint32_t m = 6;
  uint32_t d = 30;

  std::cout << "Calendar week:" << calendar_week(y, m, d) << std::endl;
  std::cout << "Day of year:" << day_of_year(y, m, d) << std::endl;

  return 0;
}
