#include <sys/types.h>
#include <unistd.h>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

namespace fs = std::experimental::filesystem;

class Log {
  fs::path path_;
  std::ofstream file_;

 public:
  Log() {
    std::ostringstream oss;

    pid_t pid = getpid();
    oss << pid;
    oss << "_log";
    std::cout << oss.str() << std::endl;

    path_ = fs::temp_directory_path() / (oss.str());
    file_.open(path_.c_str(), std::ios::out | std::ios::trunc);
  }

  ~Log() noexcept {
    try {
      if (file_.is_open()) {
        file_.close();
      }

      if (!path_.empty()) {
        fs::remove(path_);
      }
    } catch (...) {
    }
  }

  void persist(fs::path const& path) {
    file_.close();
    fs::rename(path_, path);
    path_.clear();
  }

  Log& operator<<(const std::string& message) {
    file_ << message.c_str() << '\n';
    return *this;
  }
};

int main() {
  Log log;

  try {
    log << "this is a line"
        << "and this is another one";
    throw std::runtime_error("error");
  } catch (...) {
    log.persist(R"(lastlog.txt)");
  }

  return 0;
}
