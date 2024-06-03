//
// Created by simrat39 on 12/26/23.
//

#include <gtkmm/glarea.h>
#include "CavaWindow.hpp"
#include "CavaService.hpp"
#include "constants.hpp"
#include "Renderer.hpp"
#include "gtk4-layer-shell.h"
#include <gdkmm/monitor.h>
#include <gdk/gdk.h>

CavaWindow::CavaWindow()
{
    renderer = new Renderer();

    cs = new CavaService{};
    cs->signal_data.connect(sigc::mem_fun(*this, &CavaWindow::on_data));

    fixed.put(gl_area, X_OFFSET, Y_OFFSET);

    gl_area.set_size_request(WIDTH, HEIGHT);
    gl_area.set_required_version(4, 6);
    gl_area.signal_realize().connect(sigc::mem_fun(*this, &CavaWindow::gl_on_realize));
    gl_area.signal_render().connect(sigc::mem_fun(*this, &CavaWindow::on_render), false);

    set_child(fixed);
}

void CavaWindow::on_data(const float *dataIn)
{
    for (int i = 0; i < NUM_BARS; ++i)
    {
        data[i] = dataIn[i];
    }
    gl_area.queue_render();
}

void CavaWindow::gl_on_realize()
{
    gl_area.make_current();
    renderer->pre_render();
}

bool CavaWindow::on_render(const Glib::RefPtr<Gdk::GLContext> &ctx)
{
    renderer->render(data);
    return true;
}

CavaWindow::~CavaWindow() = default;
