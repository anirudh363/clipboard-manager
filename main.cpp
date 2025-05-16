#include <gtkmm/application.h>
#include "clipboard_window.h"

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.anirudh.clipboard");

    ClipboardWindow window;

    // Start the application
    return app->run(window);
}

