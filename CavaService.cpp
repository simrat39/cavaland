//
// Created by simrat39 on 12/26/23.
//

#include "CavaService.hpp"
#include "ConfigManager.hpp"
#include "constants.hpp"
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <thread>

CavaService::CavaService(): cfg_mgr(ConfigManager::get_instance()) {
  dispatcher.connect([this]() { process_queue(); });

  std::thread([&]() {
    std::string cava_config = generate_config();
    std::cout << cava_config << std::endl;
    std::string command = "cava -p " + cava_config;

    int cfg_bars = cfg_mgr.get_or_default("bars", 120);

    FILE *pipe = popen(command.c_str(), "r");
    if (!pipe) {
      std::cerr << "Error opening pipe to command." << std::endl;
      return EXIT_FAILURE;
    }

    // Create a stream to read from the pipe
    char buffer[cfg_bars * 2];
    float data[NUM_BARS_MAX]{0};

    while (true) {
      auto bytes_read = fread(buffer, 1, cfg_bars * 2, pipe);
      if (bytes_read < cfg_bars * 2)
        continue;

      const uint16_t *uint16Buffer = reinterpret_cast<const uint16_t *>(buffer);
      for (int i = 0; i < cfg_bars; ++i) {
        data[i] = static_cast<float>(uint16Buffer[i]) / 65535;
      }
      enqueue(data);
      dispatcher.emit();
    }

    // Close the pipe
    pclose(pipe);
    return EXIT_SUCCESS;
  }).detach();
}

void CavaService::enqueue(float *data) {
  std::lock_guard<std::mutex> m{queue_mutex};
  queue.push(data);
}

void CavaService::process_queue() {
  std::lock_guard<std::mutex> m{queue_mutex};

  while (!queue.empty()) {
    auto top = queue.front();
    queue.pop();
    signal_data.emit(top);
  }
}

std::string CavaService::generate_config() {
  int cfg_bars = cfg_mgr.get_or_default("bars", 120);

  std::string contents = std::format("[general]\n"
                                     "bars = {}\n"
                                     "[output]\n"
                                     "method = raw\n",
                                     cfg_bars);

  auto tmp_dir = std::filesystem::temp_directory_path();

  auto now = std::chrono::system_clock::now();
  auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
                       now.time_since_epoch())
                       .count();

  std::filesystem::path tmp_file_name =
      tmp_dir / ("cavaland_cava_config_" + std::to_string(timestamp));

  std::ofstream tmp_file{tmp_file_name};

  if (!tmp_file.is_open()) {
    std::cerr << "Failed to open the temporary file for writing\n";
    return nullptr;
  }
  tmp_file << contents;

  return tmp_file_name.string();
}

CavaService::~CavaService() = default;
