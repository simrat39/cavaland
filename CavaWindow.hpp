//
// Created by simrat39 on 12/26/23.
//

#pragma once

#include "CavaService.hpp"
#include "ConfigManager.hpp"
#include "Renderer.hpp"
#include "constants.hpp"
#include <gtkmm/box.h>
#include <gtkmm/fixed.h>
#include <gtkmm/glarea.h>
#include <gtkmm/window.h>

class CavaWindow : public Gtk::Window {
public:
  CavaWindow();
  ~CavaWindow() override;

private:
  ConfigManager &cfg_mgr;
  Renderer *renderer;
  float data[NUM_BARS_MAX]{};
  CavaService *cs;

  Gtk::GLArea gl_area;
  Gtk::Fixed fixed;

  void gl_on_realize();
  bool on_render(const Glib::RefPtr<Gdk::GLContext> &ctx);
  void on_data(const float *);
};
