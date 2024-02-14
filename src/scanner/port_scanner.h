#pragma once

#include <boost/asio.hpp>
#include <map>

namespace scanner {

struct PortRange {
  int start = 0;
  int end = 65535;
};

struct PortScanningResult {
  bool is_open = false;
};

class PortScanner {
 public:
  explicit PortScanner(boost::asio::io_context &io_context);

  std::map<int, PortScanningResult> ScanPortRanges(std::string_view host, const std::vector<PortRange>& ports);

 private:
  void ScanPorts(std::string_view host, std::pair<int, int> ports, std::map<int, PortScanningResult>& result);

  boost::asio::io_context &io_context;
};

}