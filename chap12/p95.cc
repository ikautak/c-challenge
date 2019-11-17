#include <iostream>

#define ASIO_STANDALONE
#include "asio.hpp"

std::vector<std::string> get_ip_address(std::string const& hostname) {
  std::vector<std::string> ips;

  try {
    asio::io_context context;
    asio::ip::tcp::resolver resolver(context);
    auto endpoints =
        resolver.resolve(asio::ip::tcp::v4(), hostname.c_str(), "");

    for (auto const& e : endpoints) {
      ips.push_back(e.endpoint().address().to_string());
    }
  } catch (std::exception const& e) {
    std::cerr << "exception: " << e.what() << std::endl;
  }

  return ips;
}

int main() {
  auto ips = get_ip_address("packtpub.com");
  for (auto const& ip : ips) {
    std::cout << ip << std::endl;
  }

  return 0;
}
