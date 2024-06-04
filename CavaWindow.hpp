//
// Created by simrat39 on 12/26/23.
//

#pragma once

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/glarea.h>
#include <gtkmm/fixed.h>
#include "CavaService.hpp"
#include "constants.hpp"
#include "Renderer.hpp"

class CavaWindow : public Gtk::Window {
public:
    CavaWindow();
    ~CavaWindow() override;
private:
    Renderer* renderer;
    float data[NUM_BARS_MAX]{};
    CavaService* cs;

    Gtk::GLArea gl_area;
    Gtk::Fixed fixed;

    void gl_on_realize();
    bool on_render(const Glib::RefPtr<Gdk::GLContext> & ctx);
    void on_data(const float*);
};
