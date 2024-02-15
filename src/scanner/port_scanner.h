#pragma once

#include <boost/asio.hpp>
#include <map>

namespace scanner {

struct PortRange {
  int start = 0;
  int end = 65535;
};

struct HostConfig {
  std::vector<PortRange> port_ranges;
  std::vector<int> single_ports;
};

struct PortScanningResult {
  bool is_open = false;
};

class PortScanner {
 public:
  explicit PortScanner(boost::asio::io_context &io_context);

  void ScanSinglePorts(std::string host, const std::vector<int> &ports, std::map<int, scanner::PortScanningResult> &result);
  void ScanPortRanges(std::string host, const std::vector<PortRange>& ports, std::map<int, scanner::PortScanningResult> &result);

 private:
  void ScanPort(std::string host, int port, std::map<int, PortScanningResult>& result);

  boost::asio::io_context &io_context;
};

}