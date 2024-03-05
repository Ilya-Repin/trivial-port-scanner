#include "app/application.h"

namespace app {

using namespace std::literals;

Application::Application(boost::asio::io_context &io_context) : io_context(io_context) {}

void Application::ScanHosts(const std::unordered_map<std::string, util::HostConfig> &hosts) {
  std::vector<std::jthread> threads;
  scanner::PortScanner scanner(io_context);

  for (const auto &host : hosts) {
    threads.push_back(std::jthread([this, &scanner, host]() {
      logger::LogInfo(fmt::format("Scanning host {} started", host.first));

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

void Application::SetReportsDir(const std::string& reports_dir) {
  reports_dir_ = reports_dir;
}
}  // namespace app
