# Clipboard Manager for Ubuntu/Linux (GTKmm + X11)

A clipboard manager with a hotkey listener for Ubuntu.
Use Meta+z/Win+c shortcut to open clipboard.

A custom clipboard manager for Ubuntu/Linux built from scratch in C++ using GTKmm (GTK3) for the user interface and X11 for global hotkey handling. The project focuses on understanding clipboard internals, global keyboard hooks, GUI event loops, and Linux user-level services such as systemd. It is primarily a learning-driven project rather than a fully polished product, and reflects hands-on exploration of real-world Linux desktop and X11 behavior.


## Requirements

- GTKmm 3 development libraries (`libgtkmm-3.0-dev`)
- `g++` compiler
- systemd user session

## Build & Install

```bash
git clone https://github.com/YOUR_USERNAME/clipboard-manager.git
cd clipboard-manager
chmod +x install.sh
./install.sh

