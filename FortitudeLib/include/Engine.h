#pragma once
#include <SFML/Graphics.hpp>
#include "WindowManager.h"


class Engine
{
private:
    WindowManager window;

    // Private functions for internal use only
    void input();
    void update(float dtAsSeconds);
    void draw();

public:
    // The Engine constructor
    Engine();

    // start will call all the private functions
    void GameLoop();

};