#!/bin/bash
set -e

echo "Building clipboard manager..."
make

echo "Installing executables to /usr/local/bin..."
sudo cp hotkey_listener clipboard_window /usr/local/bin/
sudo chmod +x /usr/local/bin/hotkey_listener /usr/local/bin/clipboard_window

echo "Installing systemd user service..."
mkdir -p ~/.config/systemd/user/
cp clipboard-hotkey.service ~/.config/systemd/user/

echo "Reloading systemd daemon..."
systemctl --user daemon-reload

echo "Enabling clipboard-hotkey service..."
systemctl --user enable clipboard-hotkey.service

echo "Starting clipboard-hotkey service..."
systemctl --user start clipboard-hotkey.service

echo "Installation complete! Service started."

