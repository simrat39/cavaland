//
// Created by simrat39 on 12/26/23.
//

#include "CavalandApp.hpp"
#include "CavaWindow.hpp"
#include "gtk4-layer-shell.h"

CavalandApp::CavalandApp(): Gtk::Application() {}

Glib::RefPtr<CavalandApp> CavalandApp::create() {
    return Glib::make_refptr_for_instance(new CavalandApp());
}

void CavalandApp::on_activate() {
    Application::on_activate();

    auto window = Gtk::make_managed<CavaWindow>();

    gtk_layer_init_for_window(window->gobj());
    gtk_layer_set_layer(window->gobj(), GtkLayerShellLayer::GTK_LAYER_SHELL_LAYER_BACKGROUND);

    static const gboolean anchors[] = {TRUE, TRUE, TRUE, TRUE};
    for (int i = 0; i < GTK_LAYER_SHELL_EDGE_ENTRY_NUMBER; i++) {
        gtk_layer_set_anchor(window->gobj(), static_cast<GtkLayerShellEdge>(i), anchors[i]);
    }

    add_window(*window);
    window->present();
    window->show();
}
