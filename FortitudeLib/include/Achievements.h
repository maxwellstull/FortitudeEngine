#include <SFML/Graphics.hpp>
#include "Achievement.h"
#include <vector>

class Engine;

class Achievements
{
private:
	Engine* engine = nullptr;
	std::vector<Achievement> locked;
	std::vector<Achievement> unlocked;

public:

	void pollAchievements();
};