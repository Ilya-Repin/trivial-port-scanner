#pragma once

#include <boost/asio.hpp>
#include <string_view>
#include "../scanner/port_scanner.h"

namespace app {

class Application {
 public:
  explicit Application(boost::asio::io_context &io_context);

  void ScanHosts(const std::unordered_map<std::string, scanner::HostConfig>& hosts);
  void SetReportsDir(std::string reports_dir);

 private:
  boost::asio::io_context &io_context;
  std::string reports_dir_;
};

}