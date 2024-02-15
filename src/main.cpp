#include <iostream>
#include <boost/asio.hpp>
#include "app/application.h"
#include "util/config_parser/config_parser.h"
#include "util/logger/logger.h"
#include "util/program_options/command_line_parser.h"

using namespace boost::asio;
using namespace std::literals;

int main(int argc, char *argv[]) {
  logger::LoggerInit();

  try {
    auto programm_args = util::ParseCommandLine(argc, argv);

    if (programm_args) {
      logger::LogInfo("Service started"sv);

      boost::asio::io_context io_context;
      app::Application application(io_context);

      util::ConfigParser config;
      auto scanning_config = config.Parse(programm_args.value().config_file);

      application.SetReportsDir(scanning_config.reports_dir);
      application.ScanHosts(scanning_config.hosts);

      io_context.run();

      logger::LogInfo("Scanning finished!"sv);
    }
  } catch (std::exception &e) {
    logger::LogFatal(e.what());
  }
  return EXIT_SUCCESS;
}