#include "port_scanner.h"
#include <iostream>

namespace scanner {

PortScanner::PortScanner(boost::asio::io_context &io_context) : io_context(io_context) {}

std::map<int, PortScanningResult> PortScanner::ScanPortRanges(std::string_view host,
                                                              const std::vector<PortRange> &ports) {
  std::map<int, PortScanningResult> result;

  for (const auto &port_range : ports) {

    const int start = port_range.start;
    const int end = port_range.end;

    ScanPorts(host, std::make_pair(start, end), result);
  }

  return result;
}

void PortScanner::ScanPorts(std::string_view host, std::pair<int, int> ports, std::map<int, PortScanningResult>& result) {
  for (int port = ports.first; port <= ports.second; ++port) {
    if (result.find(port) != result.end()) {
      continue;
    }

    try {
      auto endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address(host), port);
      boost::asio::ip::tcp::socket socket{io_context};

      boost::system::error_code ec;

      socket.connect(endpoint, ec);

      if (!ec) {
        result[port] = PortScanningResult(true);
      } else {
        result[port] = PortScanningResult(false);
      }
    } catch (std::exception& e) {
      result[port] = PortScanningResult(false);
    }
  }
}

} // namespace scanner