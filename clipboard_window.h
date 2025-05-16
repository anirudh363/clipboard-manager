#pragma once

#include <gtkmm.h>
#include <vector>

class ClipboardWindow : public Gtk::Window {
public:
    ClipboardWindow();
    bool alternate = false;


private:
    Gtk::Box main_box;
    Gtk::ScrolledWindow scrolled_window;
    Gtk::ListBox clipboard_list;  

    void setup_clipboard_monitor();
    void add_clipboard_text(const Glib::ustring& text);
    void on_row_selected(Gtk::ListBoxRow* row);
};
