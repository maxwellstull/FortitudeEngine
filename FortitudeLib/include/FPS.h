#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
class FPS
{
private:
	sf::Text fpsDisplay;
	sf::Font font;
	int frameCtr;
	float frameTime;
	int fps;
	bool visible;
public:
	FPS();
	void init();
	void Draw(sf::RenderWindow* context);
	void log(float frametime);
	int get();
	void enable() { visible = true; }
	void disable() { visible = false;}
	bool isActive() { return visible; }
};