#include <SFML/Graphics.hpp>
#include "Enemy.h"

class TrainRobber : public Enemy
{
private:
	sf::Texture* _horseTexture;
	sf::Sprite _horseSprite;

public:
	TrainRobber(Attributes attr, sf::Texture* tex, double scale);
	void update(float dtAsSeconds);
	void draw(sf::RenderWindow* context);
	void setHorseTexture(sf::Texture* tex, double scale);
	void setLocation(sf::Vector2f loc);
};