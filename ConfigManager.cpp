#include "ConfigManager.hpp"
#include <cstdlib>
#include <iostream>
#include <string>
#include <libconfig.h++>

ConfigManager::ConfigManager() {}
ConfigManager::~ConfigManager() = default;

ConfigManager& ConfigManager::get_instance() {
  static ConfigManager instance;
  return instance;
}

void ConfigManager::init(std::string cfg_file) {
  try {
  config.readFile(cfg_file);
  } catch (const libconfig::ParseException& e) {
    std::cerr << e.what() << std::endl;
    exit(1);
  }
}

std::string ConfigManager::get_or_default(std::string key, std::string def) {
  try {
    return config.lookup(key).c_str();
  } catch (const libconfig::SettingNotFoundException& e) {
    std::cerr << e.what() << std::endl;
    return def;
  }
}
