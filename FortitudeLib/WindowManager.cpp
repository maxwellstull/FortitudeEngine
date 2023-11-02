#include "include/WindowManager.h"


WindowManager::WindowManager()
{
	desktopsize.x = sf::VideoMode::getDesktopMode().width;
	desktopsize.y = sf::VideoMode::getDesktopMode().height;
}
void WindowManager::init()
{
	window.create(sf::VideoMode(defaultwindow.x, defaultwindow.y), "Window", sf::Style::Default);
	window.setVerticalSyncEnabled(vsync);
}