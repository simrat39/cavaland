//
// Created by simrat39 on 12/26/23.
//

#pragma once

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
    std::queue<float*> queue;
    std::mutex queue_mutex;

    Glib::Dispatcher dispatcher;

    std::string generate_config();
};
