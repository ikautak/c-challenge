#include <iomanip>
#include <iostream>
#include <vector>

void pascal(int n) {
  std::vector<std::vector<int>> data(n, std::vector<int>(n, 0));

  for (int y = 0; y < n; ++y) {
    for (int x = 0; x < n; ++x) {
      if (x == 0) {
        data[y][0] = 1;
      } else if (x == y) {
        data[y][x] = 1;
      } else {
        try {
          auto prev_line = data.at(y - 1);
          data[y][x] = prev_line[x - 1] + prev_line[x];

        } catch (std::exception& e) {
          // ignore
        }
      }
    }
  }

  for (int y = 0; y < n; ++y) {
    for (int i = 0; i < (n - y); ++i) {
      std::cout << " ";
    }

    for (auto& v : data[y]) {
      if (v == 0) {
        break;
      }

      std::cout << v << " ";
    }
    std::cout << std::endl;
  }
}

int main() {
  pascal(10);

  return 0;
}
