#include "application.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <thread>

namespace app {

using namespace std::literals;

Application::Application(boost::asio::io_context &io_context) : io_context(io_context) {}

void Application::ScanHosts(const std::unordered_map<std::string, std::vector<scanner::PortRange>> &hosts) {
  std::vector<std::jthread> threads;
  for (const auto &host : hosts) {

    threads.push_back(std::jthread([this, host]() {
      std::cout << "scanning host "s + host.first + " began"s << std::endl; // TODO Remove couts
      scanner::PortScanner scanner(io_context);
      std::map<int, scanner::PortScanningResult> result = scanner.ScanPortRanges(host.first, host.second);

      if (!std::filesystem::exists("./scanner_reports/"s)) {
        std::filesystem::create_directory("./scanner_reports/"s);
      }

      std::string filename = "./scanner_reports/"s + host.first + "_report.txt"s;
      std::ofstream outfile(filename);
      if (!outfile.is_open()) {
        std::cerr << "Error: Failed to open file for writing"s << std::endl;
        return;
      }

      for (const auto &port_report : result) {
        std::string result_str = port_report.second.is_open ? "OPENED" : "CLOSED";
        outfile << "TCP " << host.first << " " << port_report.first << " " << result_str << std::endl;
      }
      std::cout << "scanning host "s + host.first + " finished"s << std::endl;

    }));
  }
}

} // namespace app