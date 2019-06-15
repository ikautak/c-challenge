#include <experimental/filesystem>
#include <iostream>
#include <numeric>

namespace fs = std::experimental::filesystem;

uint64_t get_directory_size(fs::path const& dir, bool const symlink = false) {
  auto iterator = fs::recursive_directory_iterator(
      dir, symlink ? fs::directory_options::follow_directory_symlink
                   : fs::directory_options::none);
  uint64_t ret = 0;
  for (auto x : iterator) {
    std::cout << x.path() << std::endl;
    if (fs::is_regular_file(x)) {
      ret += fs::file_size(x.path());
    }
  }

  return ret;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "input dir name." << std::endl;
    return 0;
  }

  std::string path = argv[1];
  std::cout << get_directory_size(path) << std::endl;
}
