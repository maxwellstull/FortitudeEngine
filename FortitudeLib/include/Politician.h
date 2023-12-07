#include <SFML/Graphics.hpp>
#include "Enemy.h"

class Politician : public Enemy
{
private:
	sf::Texture* _bodyTex;
	sf::Sprite _bodySpr;
public:
	Politician(Attributes attr, sf::Texture* tex, double scale);
	void update(float dtAsSeconds);
	void draw(sf::RenderWindow* context) override;
	void setLocation(sf::Vector2f loc);
};