#include <experimental/filesystem>
#include <iostream>
#include <regex>

namespace fs = std::experimental::filesystem;

std::vector<fs::directory_entry> find_file(fs::path& dir, std::string pattern) {
  std::vector<fs::directory_entry> result;
  std::regex rx(pattern.c_str());
  auto iterator = fs::recursive_directory_iterator(dir);

  for (auto x : iterator) {
    // std::cout << x.path() << std::endl;
    if (fs::is_regular_file(x) &&
        std::regex_match(x.path().filename().string(), rx)) {
      result.push_back(x);
    }
  }

  return result;
}

int main(int argc, char* argv[]) {
  fs::path path = R"(../)";
  std::string pattern = R"(.+cc)";
  auto result = find_file(path, pattern);

  for (auto& x : result) {
    std::cout << x.path() << std::endl;
  }
}
