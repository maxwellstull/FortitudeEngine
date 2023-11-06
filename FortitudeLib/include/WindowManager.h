#pragma once
#include <SFML/Graphics.hpp>


class WindowManager {
private:
    sf::RenderWindow window;
    int framerate = 60;
    bool vsync = true;
    bool fullscreen = false;
    bool infocus = false;
    sf::Vector2i desktopsize;
    sf::Vector2i defaultwindow = sf::Vector2i(1920,1080);
public:
    WindowManager();
    sf::RenderWindow* GetWindow() { return &window; }
    void init();
    bool isOpen() { return window.isOpen(); }
    void close() { window.close(); }
    void clear(sf::Color clr) { window.clear(clr); }
    void display() { window.display(); }
    void setFocus() { infocus = true; }
    void clearFocus() { infocus = false; }
};