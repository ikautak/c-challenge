#include <array>
#include <iostream>

class ipv4 {
 public:
  ipv4() : ipv4(0, 0, 0, 0) {}
  ipv4(uint8_t a, uint8_t b, uint8_t c, uint8_t d) : data{{a, b, c, d}} {}
  ipv4(uint32_t a) : ipv4(a >> 24, (a >> 16) & 0xff, (a >> 8) & 0xff, a & 0xff) {}
  ipv4(const ipv4& x) : data(x.data) {}
  ipv4& operator=(const ipv4& x) {
    data = x.data;
    return *this;
  }

  uint32_t get_uint32_t(void) const {
    uint32_t a = data[0];
    a = (a << 8) | data[1];
    a = (a << 8) | data[2];
    a = (a << 8) | data[3];
    return a;
  }

  friend std::ostream& operator<<(std::ostream& os, const ipv4& x) {
    os << static_cast<int>(x.data[0]) << '.' << static_cast<int>(x.data[1])
       << '.' << static_cast<int>(x.data[2]) << '.'
       << static_cast<int>(x.data[3]);
    return os;
  }

  friend std::istream& operator>>(std::istream& is, ipv4& x) {
    char d1, d2, d3;
    int b1, b2, b3, b4;
    is >> b1 >> d1 >> b2 >> d2 >> b3 >> d3 >> b4;
    if ((d1 == '.') && (d2 == '.') && (d3 == '.')) {
      x = ipv4(b1, b2, b3, b4);
    } else {
      is.setstate(std::ios_base::failbit);
    }

    return is;
  }

  ipv4& operator++() {
    *this = ipv4(get_uint32_t() + 1);
    return *this;
  }

  ipv4 operator++(int) {
    ipv4 ret = *this;
    ++(*this);
    return ret;
  }

  bool operator==(ipv4& a) {
    return a.data == data;
  }

  bool operator!=(ipv4& a) {
    return !(a == *this);
  }

  bool operator<(ipv4& a) {
    return get_uint32_t() < a.get_uint32_t();
  }

  bool operator>(ipv4& a) {
    return get_uint32_t() > a.get_uint32_t();
  }

  bool operator<=(ipv4& a) {
    return !(*this > a);
  }

  bool operator>=(ipv4& a) {
    return !(*this < a);
  }

 private:
  std::array<uint8_t, 4> data;
};

int main() {
  ipv4 a1(192, 168, 0, 1);
  ipv4 a2(192, 168, 1, 1);
  std::cout << a1 << std::endl;
  std::cout << a2 << std::endl;

  for (ipv4 a = a1; a <= a2; ++a) {
    std::cout << a << std::endl;
  }

  return 0;
}
