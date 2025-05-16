CXX = g++
CXXFLAGS = -Wall -std=c++17 `pkg-config --cflags gtkmm-3.0`
LDFLAGS = `pkg-config --libs gtkmm-3.0`

all: hotkey_listener clipboard_window

hotkey_listener: hotkey_listener.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clipboard_window: clipboard_window.cpp clipboard_window.h main.cpp
	$(CXX) $(CXXFLAGS) clipboard_window.cpp main.cpp -o $@ $(LDFLAGS)

clean:
	rm -f hotkey_listener clipboard_window
