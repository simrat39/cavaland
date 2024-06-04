//
// Created by simrat39 on 12/26/23.
//

#include "CavaWindow.hpp"
#include "CavaService.hpp"
#include "ConfigManager.hpp"
#include "Renderer.hpp"
#include "constants.hpp"
#include "gdkmm/display.h"
#include <gdk/gdk.h>
#include <gdkmm/monitor.h>
#include <gtkmm/glarea.h>

CavaWindow::CavaWindow() : cfg_mgr(ConfigManager::get_instance()) {
  renderer = new Renderer();

  cs = new CavaService{};
  cs->signal_data.connect(sigc::mem_fun(*this, &CavaWindow::on_data));

  float cfg_width = cfg_mgr.get_or_default("width", DEFAULT_WIDTH);
  float cfg_height = cfg_mgr.get_or_default("height", DEFAULT_HEIGHT);

  fixed.put(gl_area, 0, 0);
  gl_area.set_size_request(cfg_width, cfg_height);
  gl_area.set_required_version(4, 6);
  gl_area.signal_realize().connect(
      sigc::mem_fun(*this, &CavaWindow::gl_on_realize));
  gl_area.signal_render().connect(sigc::mem_fun(*this, &CavaWindow::on_render),
                                  false);

  set_child(fixed);
}

void CavaWindow::on_data(const float *dataIn) {
  for (int i = 0; i < NUM_BARS_MAX; ++i) {
    data[i] = dataIn[i];
  }
  gl_area.queue_render();
}

void CavaWindow::gl_on_realize() {
  auto display = gdk_display_get_default();
  auto surface = get_surface()->gobj();
  auto mon = gdk_display_get_monitor_at_surface(display, surface);
  GdkRectangle monitor_geom{};
  gdk_monitor_get_geometry(mon, &monitor_geom);

  float cfg_height = cfg_mgr.get_or_default("height", DEFAULT_HEIGHT);
  fixed.move(gl_area, X_OFFSET, monitor_geom.height - cfg_height - Y_OFFSET);

  gl_area.make_current();
  renderer->pre_render();
}

bool CavaWindow::on_render(const Glib::RefPtr<Gdk::GLContext> &ctx) {
  renderer->render(data);
  return true;
}

CavaWindow::~CavaWindow() = default;
