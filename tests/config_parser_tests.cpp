#define CATCH_CONFIG_MAIN

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>

#include "util/config_parser/config_parser.h"

struct DefaultConfigParser {
  util::ConfigParser config_parser;
  DefaultConfigParser() {
   logger::LoggerInit();
  }
};

TEST_CASE_METHOD(DefaultConfigParser, "Valid-Config", "[ConfigParser]") {
  util::ScanningConfig scanning_config = config_parser.Parse("../tests/test_configs/test_config_valid.json");

  REQUIRE(scanning_config.reports_dir == "scanner_reports");

  REQUIRE(scanning_config.hosts.size() == 2);

  REQUIRE(scanning_config.hosts.at("127.0.0.1").single_ports.size() == 3);
  REQUIRE(scanning_config.hosts.at("127.0.0.1").port_ranges.size() == 2);

  REQUIRE(scanning_config.hosts.at("example.com").single_ports.size() == 3);
  REQUIRE(scanning_config.hosts.at("example.com").port_ranges.size() == 2);
}

TEST_CASE_METHOD(DefaultConfigParser, "Invalid-Config", "[ConfigParser]") {
  REQUIRE_THROWS(config_parser.Parse("../tests/test_configs/test_config_invalid.json"));
}

TEST_CASE_METHOD(DefaultConfigParser, "Empty-Config", "[ConfigParser]") {
  util::ScanningConfig scanning_config = config_parser.Parse("../tests/test_configs/test_config_empty.json");

  REQUIRE(scanning_config.hosts.empty());
  REQUIRE(scanning_config.reports_dir.empty());
}

TEST_CASE_METHOD(DefaultConfigParser, "No-Dir-Config", "[ConfigParser]") {
  util::ScanningConfig scanning_config = config_parser.Parse("../tests/test_configs/test_config_no_dir.json");

  REQUIRE(scanning_config.reports_dir == "scanner_reports");

  REQUIRE(scanning_config.hosts.size() == 1);

  REQUIRE(scanning_config.hosts.at("127.0.0.1").single_ports.size() == 2);
  REQUIRE(scanning_config.hosts.at("127.0.0.1").port_ranges.empty());
}

TEST_CASE_METHOD(DefaultConfigParser, "No-Ports-Config", "[ConfigParser]") {
  util::ScanningConfig scanning_config = config_parser.Parse("../tests/test_configs/test_config_no_ports.json");

  REQUIRE(scanning_config.reports_dir == "test_reports");

  REQUIRE(scanning_config.hosts.size() == 1);

  REQUIRE(scanning_config.hosts.at("example.com").single_ports.empty());
  REQUIRE(scanning_config.hosts.at("example.com").port_ranges.empty());
}

TEST_CASE_METHOD(DefaultConfigParser, "No-Ranges-Config", "[ConfigParser]") {
  util::ScanningConfig scanning_config = config_parser.Parse("../tests/test_configs/test_config_no_ranges.json");

  REQUIRE(scanning_config.reports_dir == "test_reports");

  REQUIRE(scanning_config.hosts.size() == 1);

  REQUIRE(scanning_config.hosts.at("127.0.0.1").single_ports.size() == 2);
  REQUIRE(scanning_config.hosts.at("127.0.0.1").port_ranges.empty());
}

TEST_CASE_METHOD(DefaultConfigParser, "No-Single-Config", "[ConfigParser]") {
  util::ScanningConfig scanning_config = config_parser.Parse("../tests/test_configs/test_config_no_single.json");

  REQUIRE(scanning_config.reports_dir == "test_reports");

  REQUIRE(scanning_config.hosts.size() == 1);

  REQUIRE(scanning_config.hosts.at("127.0.0.1").single_ports.empty());
  REQUIRE(scanning_config.hosts.at("127.0.0.1").port_ranges.size() == 2);
}
