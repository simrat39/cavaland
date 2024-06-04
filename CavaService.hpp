//
// Created by simrat39 on 12/26/23.
//

#pragma once

#include "ConfigManager.hpp"
#include <queue>
#include <glibmm/dispatcher.h>

class CavaService {
public:
    CavaService();
    ~CavaService();

    void enqueue(float *data);
    void process_queue();

    sigc::signal<void(float*)> signal_data;
private:
    ConfigManager& cfg_mgr;
    std::queue<float*> queue;
    std::mutex queue_mutex;

    Glib::Dispatcher dispatcher;

    std::string generate_config();
};
