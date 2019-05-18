#include <array>
#include <iostream>

class ipv4 {
 public:
  ipv4() : ipv4(0, 0, 0, 0) {}
  ipv4(uint8_t a, uint8_t b, uint8_t c, uint8_t d) : data{{a, b, c, d}} {}
  ipv4(const ipv4& x) : data(x.data) {}
  ipv4& operator=(const ipv4& x) {
    data = x.data;
    return *this;
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

 private:
  std::array<uint8_t, 4> data;
};

int main() {
  ipv4 addr(192, 168, 0, 1);
  std::cout << addr << std::endl;

  ipv4 ip;
  std::cout << ip << std::endl;
  std::cin >> ip;
  if (!std::cin.fail()) {
    std::cout << ip << std::endl;
  }

  return 0;
}
