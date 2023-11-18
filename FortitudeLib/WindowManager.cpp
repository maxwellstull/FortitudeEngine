#include "include/WindowManager.h"


WindowManager::WindowManager()
{
	desktopsize.x = sf::VideoMode::getDesktopMode().width;
	desktopsize.y = sf::VideoMode::getDesktopMode().height;
}
void WindowManager::init()
{
	window.create(sf::VideoMode(defaultwindow.x, defaultwindow.y), "Window", sf::Style::Default);
//	window.create(sf::VideoMode(defaultwindow.x, defaultwindow.y), "Window", sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(vsync);
	sf::View view(sf::FloatRect(0, 0, 1920,1080));//defaultwindow.x, defaultwindow.y));
	window.setView(view);
	
}

sf::Vector2f WindowManager::getWindowSize()
{
	return sf::Vector2f(window.getSize().x, window.getSize().y);
}