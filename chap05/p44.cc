#include <iomanip>
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

void print_month_calendar(const int y, const uint32_t m) {
  using namespace date;
  std::cout << "Mon Tue Wed Thu Fri Sat Sun" << std::endl;

  auto first_day_weekday = week_day(y, m, 1);
  auto last_day = static_cast<uint32_t>(
      year_month_day_last(year{y}, month_day_last{month{m}}).day());

  uint32_t index = 1;
  for (uint32_t day = 1; day < first_day_weekday; ++day, ++index) {
    std::cout << "    ";
  }

  for (uint32_t day = 1; day <= last_day; ++day) {
    std::cout << std::right << std::setfill(' ') << std::setw(3) << day << " ";

    if ((index++ % 7) == 0) {
      std::cout << std::endl;
    }
  }

  std::cout << std::endl;
}

int main() {
  print_month_calendar(2019, 8);

  return 0;
}
