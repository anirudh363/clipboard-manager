#include "clipboard_window.h"
#include <glibmm.h>
#include <gtkmm/clipboard.h>
#include <iostream>

ClipboardWindow::ClipboardWindow()
: main_box(Gtk::ORIENTATION_VERTICAL) {

    auto css_provider = Gtk::CssProvider::create();
css_provider->load_from_data(R"(
    .alternate-row {
        background-color:rgb(255, 158, 47);
        color: black;
    }

    row {
        padding: 10px;
        border-bottom: 1px solid #ccc;
    }

    row:hover {
        background-color:rgb(255, 95, 95);
        color: black;
    }
)");


auto screen = Gdk::Screen::get_default();
Gtk::StyleContext::add_provider_for_screen(screen, css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);


    set_title("Clipboard Manager");
    set_default_size(400, 300);
    set_resizable(false);

    // Configure scrolled window
    scrolled_window.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
    scrolled_window.set_min_content_height(300);
    scrolled_window.set_min_content_width(400);
    scrolled_window.add(clipboard_list);

    clipboard_list.signal_row_selected().connect(sigc::mem_fun(*this, &ClipboardWindow::on_row_selected));

    main_box.pack_start(scrolled_window, Gtk::PACK_EXPAND_WIDGET);
    add(main_box);

    show_all_children();
    setup_clipboard_monitor();
}


void ClipboardWindow::add_clipboard_text(const Glib::ustring& text) {
    auto label = Gtk::make_managed<Gtk::Label>(text);
    label->set_line_wrap(true);
    label->set_max_width_chars(40);
    label->set_line_wrap_mode(Pango::WrapMode::WRAP_WORD_CHAR);
label->set_margin_top(5);
label->set_margin_bottom(5);
label->set_margin_start(10);
label->set_margin_end(10);


    // Wrap label in a ListBoxRow
    auto row = Gtk::make_managed<Gtk::ListBoxRow>();
    row->add(*label);

    // Alternate row background for readability
    static bool alternate = false;
    if (alternate) {
        row->get_style_context()->add_class("alternate-row");
    }
    alternate = !alternate;

    clipboard_list.prepend(*row);
    row->show_all();
}


void ClipboardWindow::on_row_selected(Gtk::ListBoxRow* row) {
    if (row) {
        auto label = dynamic_cast<Gtk::Label*>(row->get_child());
        if (label) {
            auto text = label->get_text();
            auto clipboard = Gtk::Clipboard::get();
            clipboard->set_text(text);
        }
    }
}


void ClipboardWindow::setup_clipboard_monitor() {
    auto clipboard = Gtk::Clipboard::get();

    Glib::signal_timeout().connect_seconds([clipboard, this]() {
        clipboard->request_text([this](const Glib::ustring& text) {
            static Glib::ustring last_text;
            if (!text.empty() && text != last_text) {
                last_text = text;
                add_clipboard_text(text);
            }
        });
        return true;
    }, 1);
}
