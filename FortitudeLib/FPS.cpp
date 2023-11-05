#include "include/FPS.h"
#include <iostream>
FPS::FPS()
{
	fps = std::vector<float>(100);
	framedelta = std::vector<float>(100);
	index = 0;
	avg = 0;
}

void FPS::init()
{

}

void FPS::log(float frametime)
{
	std::cout <<  avg<< " " << framedelta[index] << " " << frametime<< " " << index << std::endl;
	avg = avg * 100.f;
	avg -= framedelta[index];
	avg += frametime;
	avg = avg / 100.f;

	framedelta[index] = frametime;
	index += 1;
	if (index > 99)
	{
		index = 0;
	}
}
int FPS::get()
{
	return (int)(1.f/avg);
}