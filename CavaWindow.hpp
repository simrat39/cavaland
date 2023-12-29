//
// Created by simrat39 on 12/26/23.
//

#pragma once

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/glarea.h>
#include <glm/glm.hpp>
#include "CavaService.hpp"
#include "Shader.hpp"
#include "renderers/IRenderer.hpp"
#include "constants.hpp"

class CavaWindow : public Gtk::Window {
public:
    CavaWindow();
    ~CavaWindow() override;
private:
    IRenderer* renderer;
    double data[NUM_BARS]{};
    CavaService* cs;
    Gtk::GLArea gl_area;

    void gl_on_realize();
    bool on_render(const Glib::RefPtr<Gdk::GLContext> & ctx);
    void on_data(const double*);
};
