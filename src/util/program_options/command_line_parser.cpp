#include "command_line_parser.h"
#include <iostream>

namespace util {

using namespace std::literals;

std::optional<Args> ParseCommandLine(int argc, const char *const argv[]) {
  namespace po = boost::program_options;

  po::options_description desc{"Allowed options"s};

  Args args;
  desc.add_options()

      ("help,h", "produce help message")

      ("config-file,c", po::value(&args.config_file)->value_name("file"s), "set config file path");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.contains("help"s)) {
    std::cout << desc;
    return std::nullopt;
  }

  if (!vm.contains("config-file"s)) {
    throw std::runtime_error("Config file has not been specified");
  }

  return args;
}
} // namespace util
