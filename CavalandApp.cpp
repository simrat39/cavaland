//
// Created by simrat39 on 12/26/23.
//

#include "CavalandApp.hpp"
#include "CavaWindow.hpp"
#include "gtk4-layer-shell.h"
#include <gtkmm/cssprovider.h>
#include <string>

CavalandApp::CavalandApp() : Gtk::Application() {}

Glib::RefPtr<CavalandApp> CavalandApp::create()
{
  return Glib::make_refptr_for_instance(new CavalandApp());
}

void CavalandApp::on_activate()
{
  Application::on_activate();

  auto window = Gtk::make_managed<CavaWindow>();

  gtk_layer_init_for_window(window->gobj());
  gtk_layer_set_layer(window->gobj(),
                      GtkLayerShellLayer::GTK_LAYER_SHELL_LAYER_BACKGROUND);
  gtk_layer_set_exclusive_zone(window->gobj(), -1);

  static const gboolean anchors[] = {TRUE, TRUE, TRUE, TRUE};
  for (int i = 0; i < GTK_LAYER_SHELL_EDGE_ENTRY_NUMBER; i++)
  {
    gtk_layer_set_anchor(window->gobj(), static_cast<GtkLayerShellEdge>(i),
                         anchors[i]);
  }

  auto provider = Gtk::CssProvider::create();
  auto css = "window{background:none;} *{transform: rotate(0deg);}";
  provider->load_from_string(css);

  Gtk::StyleContext::add_provider_for_display(
      Gdk::Display::get_default(), provider,
      GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  add_window(*window);

  window->present();
  window->show();
}
