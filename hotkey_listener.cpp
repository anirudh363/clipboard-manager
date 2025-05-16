#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>

// Modifier masks to cover NumLock and CapsLock
const unsigned int modifiers[] = {
    Mod4Mask,
    Mod4Mask | Mod2Mask,   // NumLock
    Mod4Mask | LockMask,   // CapsLock
    Mod4Mask | Mod2Mask | LockMask
};

int main() {
    Display* display = XOpenDisplay(nullptr);
    if (!display) {
        std::cerr << "Cannot open X display\n";
        return 1;
    }

    Window root = DefaultRootWindow(display);
    int keycode = XKeysymToKeycode(display, XStringToKeysym("z"));

    // Grab the key with different modifier combos
    for (auto mod : modifiers) {
        XGrabKey(display, keycode, mod, root, True, GrabModeAsync, GrabModeAsync);
    }

    XSelectInput(display, root, KeyPressMask);

    std::cout << "Listening for Meta+Z (Win+Z)...\n";

    while (true) {
        XEvent ev;
        XNextEvent(display, &ev);

        if (ev.type == KeyPress) {
            XKeyEvent xkey = ev.xkey;

            // Check if keycode matches and any of the modifiers match
            for (auto mod : modifiers) {
                if (xkey.keycode == keycode && (xkey.state & mod) == mod) {
                    std::cout << "Meta+Z pressed! Launching clipboard manager...\n";
                    system("./clipboard-manager &");
                    break;
                }
            }
        }
    }

    XCloseDisplay(display);
    return 0;
}
