CXX = g++
CXXFLAGS = -Wall -std=c++17 `pkg-config --cflags gtkmm-3.0`
LDFLAGS = `pkg-config --libs gtkmm-3.0` -lX11

all: hotkey_listener clipboard_window

hotkey_listener: hotkey_listener.cpp
	$(CXX) $(CXXFLAGS) hotkey_listener.cpp -o hotkey_listener $(LDFLAGS)

clipboard_window: main.cpp clipboard_window.cpp
	$(CXX) $(CXXFLAGS) main.cpp clipboard_window.cpp -o clipboard_window $(LDFLAGS)

clean:
	rm -f hotkey_listener clipboard_window
