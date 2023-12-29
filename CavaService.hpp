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

    void enqueue(double *data);
    void process_queue();

    sigc::signal<void(double*)> signal_data;
private:
    std::queue<double*> queue;
    std::mutex queue_mutex;

    Glib::Dispatcher dispatcher;
};
