#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include "../../scanner/port_scanner.h"

namespace util {

struct ScanningConfig {
  std::unordered_map<std::string, scanner::HostConfig> hosts;
  std::string reports_dir = "scanner_reports";
};

class ConfigParser {
 public:
   ScanningConfig Parse(const std::string& file_path);

 private:
  bool IsValidTree(const boost::property_tree::ptree& pt) const;
};
}
