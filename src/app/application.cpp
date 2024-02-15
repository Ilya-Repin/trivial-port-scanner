#include "application.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <thread>
#include "../util/logger/logger.h"

namespace app {

using namespace std::literals;

Application::Application(boost::asio::io_context &io_context) : io_context(io_context) {}

void Application::ScanHosts(const std::unordered_map<std::string, scanner::HostConfig> &hosts) {
  std::vector<std::jthread> threads;
  for (const auto &host : hosts) {

    threads.push_back(std::jthread([this, host]() {
      logger::LogInfo(fmt::format("Scanning host {} started", host.first));
      scanner::PortScanner scanner(io_context);

      std::map<int, scanner::PortScanningResult> result;

      scanner.ScanSinglePorts(host.first, host.second.single_ports, result);
      scanner.ScanPortRanges(host.first, host.second.port_ranges, result);


      if (!std::filesystem::exists(fmt::format("./{}/", reports_dir_))) {
        std::filesystem::create_directory(fmt::format("./{}/", reports_dir_));
      }

      std::string filename = fmt::format("./{}/{}_report.txt", reports_dir_, host.first);
      std::ofstream outfile(filename);

      if (!outfile.is_open()) {
        logger::LogError("Error: Failed to open file for writing"sv);
        return;
      }

      for (const auto &port_report : result) {
        std::string result_str = port_report.second.is_open ? "OPENED" : "CLOSED";
        outfile << "TCP " << host.first << " " << port_report.first << " " << result_str << std::endl;
      }

      logger::LogInfo(fmt::format("Scanning host {} finished. Report in {}", host.first, filename));
    }));
  }
}

void Application::SetReportsDir(std::string reports_dir) {
  reports_dir_ = reports_dir;
}

} // namespace app