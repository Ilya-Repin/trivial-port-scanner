#include <iostream>
#include <boost/asio.hpp>
#include "app/application.h"

using namespace boost::asio;

int main() {
  boost::asio::io_context io_context;
  app::Application application(io_context);


  std::string target = "127.0.0.1";
  std::string target2 = "192.168.1.1";

  std::unordered_map<std::string, std::vector<scanner::PortRange>> hosts;
  hosts[target].push_back(scanner::PortRange(8170, 8200));


  hosts[target2].push_back(scanner::PortRange(6666, 6668));

  application.ScanHosts(hosts);

  io_context.run();

  return EXIT_SUCCESS;
}