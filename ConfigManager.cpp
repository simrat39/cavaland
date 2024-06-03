#include "ConfigManager.hpp"
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <libconfig.h++>
#include <string>

ConfigManager::ConfigManager() {}
ConfigManager::~ConfigManager() = default;

ConfigManager &ConfigManager::get_instance() {
  static ConfigManager instance;
  return instance;
}

void ConfigManager::init(std::string cfg_file) {
  if (!std::filesystem::exists(cfg_file)) {
    std::cerr << "Config file not found!" << std::endl;
    return;
  }

  try {
    config.readFile(cfg_file);
  } catch (const libconfig::ParseException &e) {
    std::cerr << e.what() << std::endl;
    std::cerr << e.getLine() << std::endl;
    std::cerr << e.getError() << std::endl;
    exit(1);
  }
}
