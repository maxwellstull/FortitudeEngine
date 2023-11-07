#include "include/FPS.h"
#include <iostream>
FPS::FPS()
{
	frameCtr = 0;
	frameTime = 0;
	fps = 0;
}

void FPS::init()
{
	enable();
	font.loadFromFile("img/cowboy.ttf");
	fpsDisplay.setFillColor(sf::Color::Red);
	fpsDisplay.setFont(font);
	fpsDisplay.setPosition(30, 30);
	fpsDisplay.setCharacterSize(24);
}

void FPS::Draw(sf::RenderWindow* context)
{
	if (visible)
	{
		fpsDisplay.setString(std::to_string(fps));
		context->draw(fpsDisplay);
	}
}


void FPS::log(float frametime)
{
	frameCtr += 1;
	frameTime += frametime;
	if (frameTime > 1)
	{
		fps = frameCtr / frameTime;
//		std::cout << "Avg FPS: " << fps << "(" << frameCtr << "/" << frameTime << ")" << std::endl;
		frameCtr = 0;
		frameTime = 0;

	}
}
int FPS::get()
{
	return fps;
}