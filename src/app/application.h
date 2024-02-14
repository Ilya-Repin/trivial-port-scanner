#pragma once

#include <boost/asio.hpp>
#include <string_view>
#include "../scanner/port_scanner.h"

namespace app {


class Application {
 public:
  explicit Application(boost::asio::io_context &io_context);

  void ScanHosts(const std::unordered_map<std::string, std::vector<scanner::PortRange>>& hosts);

 private:
  boost::asio::io_context &io_context;
};

}