#pragma once

#include <unordered_map>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "util/scanning_configs/host_config.h"
#include "util/logger/logger.h"

namespace util {

class ConfigParser {
 public:
  ScanningConfig Parse(const std::string& file_path);

 private:
  bool IsValidTree(const boost::property_tree::ptree& pt) const;
};
}  // namespace util
