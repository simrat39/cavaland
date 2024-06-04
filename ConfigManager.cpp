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

float ConfigManager::get_or_default(const std::string &key, float def) {
  try {
    float ret{config.lookup(key)};
    return ret;
  } catch (const libconfig::SettingNotFoundException &e) {
    std::cerr << e.what() << std::endl;
    std::cerr << key << " not found in config." << std::endl;
    return def;
  } catch (const libconfig::SettingTypeException &e) {
    std::cerr << e.what() << std::endl;
    std::cerr << "Expected type \"float\" for key " << key
              << ", falling back to default." << std::endl;
    return def;
  }
}

int ConfigManager::get_or_default(const std::string &key, int def) {
  try {
    int ret{config.lookup(key)};
    return ret;
  } catch (const libconfig::SettingNotFoundException &e) {
    std::cerr << e.what() << std::endl;
    std::cerr << key << " not found in config." << std::endl;
    return def;
  } catch (const libconfig::SettingTypeException &e) {
    std::cerr << e.what() << std::endl;
    std::cerr << "Expected type \"int\" for key " << key
              << ", falling back to default." << std::endl;
    return def;
  }
}

std::string ConfigManager::get_or_default(const std::string &key,
                                          std::string def) {
  try {
    std::string ret{config.lookup(key).c_str()};
    return ret;
  } catch (const libconfig::SettingNotFoundException &e) {
    std::cerr << e.what() << std::endl;
    std::cerr << key << " not found in config." << std::endl;
    return def;
  } catch (const libconfig::SettingTypeException &e) {
    std::cerr << e.what() << std::endl;
    std::cerr << "Expected type \"string\" for key " << key
              << ", falling back to default." << std::endl;
    return def;
  }
}