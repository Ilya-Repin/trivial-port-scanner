#include "config_parser.h"
#include "../logger/logger.h"
#include <boost/property_tree/json_parser.hpp>

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

  scanning_config.reports_dir = pt.get<std::string>("reports_dir");

  for (const auto& host : pt.get_child("hosts")) {
    std::string hostname = host.second.get<std::string>("host");

    if (scanning_config.hosts.find(hostname) != scanning_config.hosts.end()) {
      logger::LogError("Duplicate host "s + hostname + " detected!"s);
      continue;
    }

    scanner::HostConfig host_config;

    for (const auto& port_obj : host.second.get_child("port_ranges")) {
      scanner::PortRange pr;
      pr.start = port_obj.second.get("start_port", 0);
      pr.end = port_obj.second.get("end_port", 65535);
      host_config.port_ranges.push_back(pr);
    }

    for (const auto& port : host.second.get_child("single_ports")) {
      host_config.single_ports.push_back(port.second.get_value<int>());
    }

    scanning_config.hosts[hostname] = host_config;
  }

  return scanning_config;
}

bool ConfigParser::IsValidTree(const boost::property_tree::ptree& pt) const {
  if (!pt.count("hosts")) {
    return false;
  }

  // TODO Добавить проверок

  return true;
}
}
