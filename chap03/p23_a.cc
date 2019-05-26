#include <array>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <vector>

template <typename Iter>
std::string bytes_to_hexstr(Iter begin, Iter end,
                            const bool uppercase = false) {
  std::ostringstream oss;
  if (uppercase) {
    oss.setf(std::ios_base::uppercase);
  }

  for (; begin != end; ++begin) {
    oss << std::hex << std::setw(2) << std::setfill('0')
        << static_cast<int>(*begin);
  }

  return oss.str();
}

template <typename C>
std::string bytes_to_hexstr(const C& c, const bool uppercase = false) {
  return bytes_to_hexstr(std::begin(c), std::cend(c), uppercase);
}

int main() {
  std::vector<uint8_t> v{0xBA, 0xAD, 0xF0, 0x0D};
  std::array<uint8_t, 6> a{{1, 2, 3, 4, 5, 6}};
  uint8_t buf[5] = {0x11, 0x22, 0x33, 0x44, 0x55};

  assert(bytes_to_hexstr(v, true) == "BAADF00D");
  assert(bytes_to_hexstr(a, true) == "010203040506");
  assert(bytes_to_hexstr(buf, true) == "1122334455");

  assert(bytes_to_hexstr(v) == "baadf00d");
  assert(bytes_to_hexstr(a) == "010203040506");
  assert(bytes_to_hexstr(buf) == "1122334455");

  return 0;
}
