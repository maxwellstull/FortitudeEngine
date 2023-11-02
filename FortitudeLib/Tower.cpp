#include "include/Tower.h"



void Tower::SetLocation(double x, double y)
{
	position.x = x;
	position.y = y;
}

void Tower::SetLocation(sf::Vector2f loc)
{
	position = loc;
}

void Tower::SetSpeed(double x, double y)
{
	speed.x = x;
	speed.y = y;
}

void Tower::SetSpeed(sf::Vector2f vel)
{
	speed = vel;
}

void Tower::SetRotation(double rot)
{
	rotation = rot;
}

void Tower::Update(double elapsed)
{
	
}

void Tower::Draw()
{

}
