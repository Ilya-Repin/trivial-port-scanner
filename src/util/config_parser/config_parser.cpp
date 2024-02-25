#include "util/config_parser/config_parser.h"

namespace util {

using namespace std::literals;

ScanningConfig ConfigParser::Parse(const std::string& file_path) {
  ScanningConfig scanning_config;

  boost::property_tree::ptree pt;
  boost::property_tree::json_parser::read_json(file_path, pt);

  if (!IsValidTree(pt)) {
    logger::LogError("Wrong structure of config file!"sv);
    return scanning_config;
  }

  scanning_config.reports_dir = pt.get<std::string>("reports_dir", "scanner_reports");

  for (const auto& host : pt.get_child("hosts")) {
    std::string hostname = host.second.get<std::string>("host");

    if (scanning_config.hosts.find(hostname) != scanning_config.hosts.end()) {
      logger::LogError("Duplicate host "s + hostname + " detected!"s);
      continue;
    }

    HostConfig host_config;

    if (host.second.count("port_ranges")) {
      for (const auto& port_range : host.second.get_child("port_ranges")) {
        PortRange pr;

        pr.start = port_range.second.get("from", 0);
        pr.end = port_range.second.get("to", 65535);

        host_config.port_ranges.push_back(pr);
      }
    }

    if (host.second.count("single_ports")) {
      for (const auto& port : host.second.get_child("single_ports")) {
        host_config.single_ports.push_back(port.second.get_value<int>());
      }
    }

    scanning_config.hosts[hostname] = host_config;
  }

  return scanning_config;
}

bool ConfigParser::IsValidTree(const boost::property_tree::ptree& pt) const {
  if (!pt.count("hosts")) {
    return false;
  }

  for (const auto& host : pt.get_child("hosts")) {
    if (host.second.count("host") == 0) {
      return false;
    }
  }

  return true;
}
}  // namespace util
