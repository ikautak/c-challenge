#include <experimental/filesystem>
#include <iostream>
#include <numeric>
#include <regex>
#include <string>
#include <string_view>
#include <vector>

#include "ZipArchive.h"
#include "ZipFile.h"

namespace fs = std::experimental::filesystem;

std::vector<std::string> find_in_archive(fs::path const& archivepath,
                                         std::string_view const& pattern) {
  std::vector<std::string> results;

  if (fs::exists(archivepath)) {
    try {
      auto archive = ZipFile::Open(archivepath.string());

      for (size_t i = 0; i < archive->GetEntriesCount(); ++i) {
        auto entry = archive->GetEntry(i);
        if (entry) {
          if (!entry->IsDirectory()) {
            auto name = entry->GetName();
            if (std::regex_match(name, std::regex{pattern.data()})) {
              results.push_back(entry->GetFullName());
            }
          }
        }
      }
    } catch (std::exception const& ex) {
      std::cout << ex.what() << std::endl;
    }
  }

  return results;
}

int main(int argc, char* argv[]) {
  auto results = find_in_archive("test.zip", R"(^.*\.png$)");

  for (auto const& name : results) {
    std::cout << name << std::endl;
  }

  return 0;
}
