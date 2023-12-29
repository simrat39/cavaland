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

class CavaWindow : public Gtk::Window {
public:
    CavaWindow();
    ~CavaWindow() override;
private:
    CavaService* cs;
    Gtk::GLArea gl_area;

    double data[30]{};

    GLuint VAO;
    std::array<glm::vec2, 30> offsets{};
    Shader* shader;

    void gl_on_realize();
    bool on_render(const Glib::RefPtr<Gdk::GLContext> & ctx);

    void on_data(double*);
};
