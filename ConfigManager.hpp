#pragma once

#include <iostream>
#include <libconfig.h++>
#include <string>

class ConfigManager {
public:
  libconfig::Config config;

  static ConfigManager &get_instance();

  void init(std::string cfg_file);

  template <typename T> T get_or_default(const std::string &key, T def) {
    throw "Shouldnt be here!";
  }

  template <typename t>
  float get_or_default(const std::string &key, float def) {
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

  template <typename t>
  std::string get_or_default(const std::string &key, std::string def) {
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

  ConfigManager(ConfigManager &&) = delete;

  ConfigManager(const ConfigManager &) = delete;

  ConfigManager &operator=(ConfigManager &&) = delete;

  ConfigManager &operator=(const ConfigManager &) = delete;

  ~ConfigManager();

private:
  ConfigManager();
};
