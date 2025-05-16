#!/bin/bash

echo "Uninstalling clipboard manager..."

# Stop and disable the systemd service
systemctl --user stop clipboard-hotkey.service
systemctl --user disable clipboard-hotkey.service

# Remove systemd service file
SERVICE_PATH="$HOME/.config/systemd/user/clipboard-hotkey.service"
if [ -f "$SERVICE_PATH" ]; then
    rm "$SERVICE_PATH"
    echo "Removed service file."
fi

# Reload systemd user daemon
systemctl --user daemon-reload
systemctl --user reset-failed

# Remove installed binaries
sudo rm -f /usr/local/bin/hotkey_listener
sudo rm -f /usr/local/bin/clipboard_window

echo "Clipboard manager uninstalled successfully."

