#include "CavalandApp.hpp"
#include <boost/program_options.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/value_semantic.hpp>
#include <iostream>
#include <string>
#include "ConfigManager.hpp"

int main(int argc, const char **argv) {
  namespace po = boost::program_options;

  po::options_description desc{"Allowed Options"};
  desc.add_options()("help", "print help message")(
      "config", boost::program_options::value<std::string>(), "path to the config file");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.count("help")) {
    std::cout << desc << "\n";
    return 1;
  }

  if (vm.count("config")) {
    ConfigManager::get_instance().init(vm["config"].as<std::string>());
  } else {
    ConfigManager::get_instance().init("/usr/share/cavaland/example.cfg");
  }

  auto app = CavalandApp::create();
  return app->run();
}
