#include <libconfig.h++>
#include <string>

class ConfigManager {
public:
  libconfig::Config config;

  static ConfigManager& get_instance();
  void init(std::string cfg_file);

  std::string get_or_default(std::string key, std::string def);

  ConfigManager (ConfigManager  &&) = delete;
  ConfigManager (const ConfigManager  &) = delete;
  ConfigManager  &operator=(ConfigManager  &&) = delete;
  ConfigManager  &operator=(const ConfigManager  &) = delete;
  ~ConfigManager ();
private:
  ConfigManager ();
};
