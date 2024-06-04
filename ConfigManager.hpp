#pragma once

#include <libconfig.h++>
#include <string>

class ConfigManager {
public:
  libconfig::Config config;

  static ConfigManager &get_instance();

  void init(std::string cfg_file);

  float get_or_default(const std::string &key, float def); 
  int get_or_default(const std::string &key, int def); 
  std::string get_or_default(const std::string &key, std::string def); 

  ConfigManager(ConfigManager &&) = delete;

  ConfigManager(const ConfigManager &) = delete;

  ConfigManager &operator=(ConfigManager &&) = delete;

  ConfigManager &operator=(const ConfigManager &) = delete;

  ~ConfigManager();

private:
  ConfigManager();
};
