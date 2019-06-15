#include <experimental/filesystem>
#include <iostream>

namespace fs = std::experimental::filesystem;
namespace ch = std::chrono;

template <typename Duration>
bool is_older_than(fs::path const& path, Duration const duration) {
  auto ftimeduration = fs::last_write_time(path).time_since_epoch();
  auto nowduration = (ch::system_clock::now() - duration).time_since_epoch();
  return ch::duration_cast<Duration>(nowduration - ftimeduration).count() > 0;
}

template <typename Duration>
void remove_files_older_than(fs::path const& path, Duration const duration) {
  try {
    if (fs::exists(path)) {
      std::cout << path << std::endl;
      if (is_older_than(path, duration)) {
        // fs::remove(path);
        std::cout << "remove" << std::endl;
      } else if (fs::is_directory(path)) {
        for (auto const& entry : fs::directory_iterator(path)) {
          remove_files_older_than(entry.path(), duration);
        }
      }
    }
  } catch (std::exception const& ex) {
    std::cerr << ex.what() << std::endl;
  }
}

int main() {
  using namespace std::chrono_literals;
  auto path = R"(../)";
  remove_files_older_than(path, 10h + 20min);
}
