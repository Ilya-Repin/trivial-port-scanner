#pragma once

#include <fmt/format.h>
#include <vector>
#include <string>
#include <map>
#include <boost/asio.hpp>
#include "util/logger/logger.h"
#include "util/scanning_configs/host_config.h"

namespace scanner {
struct PortScanningResult {
  bool is_open = false;
};

class PortScanner {
 public:
  explicit PortScanner(boost::asio::io_context &io_context);

  void ScanSinglePorts(std::string host, const std::vector<int> &ports, std::map<int, PortScanningResult> &result);
  void ScanPortRanges(std::string host,
                        const std::vector<util::PortRange> &ports,
                        std::map<int, PortScanningResult> &result);
 private:
  void ScanPort(std::string host, int port, std::map<int, PortScanningResult> &result);

  boost::asio::io_context &io_context;
};
}  // namespace scanner
