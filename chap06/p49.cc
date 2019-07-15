#include <iostream>
#include <map>

std::map<char, double> analyze_text(std::string_view text) {
  std::map<char, double> freq;

  size_t total = 0;
  for (auto ch : text) {
    if (std::isalpha(ch)) {
      freq[std::tolower(ch)] += 1;

      total += 1;
    }
  }
  // std::cout << "total : " << total << std::endl;

  for (auto& x : freq) {
    // std::cout << ch << " : " << c << std::endl;
    x.second = x.second / static_cast<double>(total);
  }

  return freq;
};

int main() {
  auto result = analyze_text(
      R"(Lorem ipsum dolor sit amet, consectetur adipiscing elit, )"
      R"(sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.)");

  for (auto const& [ch, rate] : result) {
    std::cout << ch << " : " << rate << std::endl;
  }

  return 0;
}
