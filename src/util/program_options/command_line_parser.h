#pragma once

#include <string>
#include <optional>
#include <filesystem>
#include <boost/program_options.hpp>

namespace util  {

struct Args {
  std::filesystem::path config_file;
};

std::optional<Args> ParseCommandLine(int argc, const char *const argv[]);

}
