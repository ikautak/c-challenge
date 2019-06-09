#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "input file" << std::endl;
    return -1;
  }

  std::ifstream ifs(argv[1]);
  if (ifs.fail()) {
    std::cout << "error" << std::endl;
    return -2;
  }

  std::string ofile = argv[1];
  ofile += "_out.txt";
  std::ofstream ofs(ofile);
  std::string buf;
  while (std::getline(ifs, buf)) {
    if (buf.length() == 0) {
      continue;
    }

    if (buf.find_first_not_of(' ') == buf.npos) {
      continue;
    }

    ofs << buf << std::endl;
  }

  return 0;
}