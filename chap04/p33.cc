#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

enum class Status { Running, Suspended };
enum class Platform { _32bit, _64bit };

std::string Status_str(Status s) {
  return (s == Status::Running) ? "Running" : "Supended";
}

std::string Platform_str(Platform p) {
  return (p == Platform::_32bit) ? "32-bit" : "64-bit";
}

class ProcessInfo {
 public:
  ProcessInfo(std::string name, int id, Status status, std::string account,
              uint64_t mem_size, Platform platform)
      : name_(name),
        id_(id),
        status_(status),
        account_(account),
        mem_size_(mem_size),
        platform_(platform) {}

  // private:
  std::string name_;
  int id_ = 0;
  Status status_ = Status::Suspended;
  std::string account_;
  uint64_t mem_size_ = 0;
  Platform platform_ = Platform::_64bit;
};

class Comp {
 public:
  bool operator()(ProcessInfo& a, ProcessInfo& b) { return a.name_ < b.name_; }
};

void print_process_info_list(std::vector<ProcessInfo>& list) {
  std::sort(list.begin(), list.end(), Comp());

  // get width
  size_t name_w = 0;
  size_t id_w = 0;
  size_t account_w = 0;
  size_t mem_w = 0;
  for (auto&& x : list) {
    size_t w = x.name_.length();
    if (w > name_w) {
      name_w = w;
    }

    w = std::to_string(x.id_).length();
    if (w > id_w) {
      id_w = w;
    }

    w = x.account_.length();
    if (w > account_w) {
      account_w = w;
    }

    w = std::to_string(x.mem_size_).length();
    if (w > mem_w) {
      mem_w = w;
    }
  }

  // print list
  for (auto&& x : list) {
    std::cout << std::left << std::setw(name_w) << x.name_ << " ";
    std::cout << std::left << std::setw(id_w) << x.id_ << " ";
    std::cout << std::left << std::setw(9) << Status_str(x.status_) << " ";
    std::cout << std::left << std::setw(account_w) << x.account_ << " ";
    std::cout << std::right << std::setw(mem_w) << x.mem_size_ << " ";
    std::cout << std::left << std::setw(6) << Platform_str(x.platform_);

    std::cout << std::endl;
  }
}

int main() {
  // clang-format off
  std::vector<ProcessInfo> list{
      {"chrome.exe",   1044,  Status::Running,   "marius.bancila", 25180,  Platform::_32bit},
      {"chrome.exe",   10100, Status::Running,   "marius.bancila", 227756, Platform::_32bit},
      {"cmd.exe",      512,   Status::Running,   "SYSTEM",         40,     Platform::_64bit},
      {"explorer.exe", 7108,  Status::Running,   "marius.bancila", 29529,  Platform::_64bit},
      {"skype.exe",    22456, Status::Suspended, "marius.bancila", 656,    Platform::_64bit},
      {"asdf.exe",     356,   Status::Suspended, "marius.bancila", 656,    Platform::_64bit}
                                 };
  // clang-format on

  print_process_info_list(list);

  return 0;
}