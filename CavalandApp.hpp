//
// Created by simrat39 on 12/26/23.
//

#pragma once

#include <gtkmm/application.h>

class CavalandApp: public Gtk::Application {
public:
    CavalandApp();
    static Glib::RefPtr<CavalandApp> create();
protected:
    void on_activate() override;
};
