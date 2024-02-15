#include "port_scanner.h"
#include "../util/logger/logger.h"

namespace scanner {

using namespace std::literals;

PortScanner::PortScanner(boost::asio::io_context &io_context) : io_context(io_context) {}

void PortScanner::ScanSinglePorts(std::string
                                  host,
                                  const std::vector<int> &ports, std::map<int, scanner::PortScanningResult>
                                  &result) {
  logger::LogInfo(fmt::format("Scanning single ports on {} started", host));

  for (const auto &port : ports) {
    ScanPort(host, port, result);
  }

  logger::LogInfo(fmt::format("Scanning single ports on {} finished", host));
}

void PortScanner::ScanPortRanges(std::string
                                 host,
                                 const std::vector<PortRange> &ports, std::map<int, scanner::PortScanningResult>
                                 &result) {
  logger::LogInfo(fmt::format("Scanning port ranges on {} started", host));

  for (const auto &port_range : ports) {

    const int start = port_range.start;
    const int end = port_range.end;

    logger::LogInfo(fmt::format("Scanning port range on {} from {} to {} started", host, start, end));

    for (int port = start; port <= end; ++port) {
      ScanPort(host, port, result);
    }

    logger::LogInfo(fmt::format("Scanning port range on {} from {} to {} finished", host, start, end));
  }

  logger::LogInfo(fmt::format("Scanning port ranges on {} finished", host));
}

void PortScanner::ScanPort(std::string host, int port,
                           std::map<int, PortScanningResult> &result) {
  if (result.find(port) != result.end()) {
    return;
  }

  try {
    auto endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address(host), port);
    boost::asio::ip::tcp::socket socket{io_context};

    boost::system::error_code ec;

    socket.connect(endpoint, ec);

    if (!ec) {
      logger::LogInfo(fmt::format("Found open port: {}:{}", host, port));
      result[port] = PortScanningResult(true);
    } else {
      result[port] = PortScanningResult(false);
    }
  } catch (std::exception &e) {
    result[port] = PortScanningResult(false);
  }
}

} // namespace scanner