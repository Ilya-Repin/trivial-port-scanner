#pragma once

#include <string>
#include <vector>
#include <unordered_map>

namespace util {

struct PortRange {
  int start = 0;
  int end = 65535;
};

struct HostConfig {
  std::vector<PortRange> port_ranges;
  std::vector<int> single_ports;
};

struct ScanningConfig {
  std::unordered_map<std::string, HostConfig> hosts;
  std::string reports_dir;
};
}  // namespace util
