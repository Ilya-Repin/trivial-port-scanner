#pragma once

#include <fmt/format.h>
#include <fstream>
#include <filesystem>
#include <thread>
#include <unordered_map>
#include <vector>
#include <string>
#include <map>
#include <boost/asio.hpp>
#include "scanner/port_scanner.h"
#include "util/logger/logger.h"
#include "util/scanning_configs/host_config.h"

namespace app {
class Application {
 public:
  explicit Application(boost::asio::io_context &io_context);

  void ScanHosts(const std::unordered_map<std::string, util::HostConfig> &hosts);
  void SetReportsDir(const std::string &reports_dir);

 private:
  boost::asio::io_context &io_context;
  std::string reports_dir_;
};
}  // namespace app
