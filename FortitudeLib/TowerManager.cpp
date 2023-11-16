#include "include/TowerManager.h"
#include "include/Game.h"


void TowerManager::update(float dtAsSeconds)
{
  for (std::shared_ptr<Tower> to : towers)
  {
    to->update(dtAsSeconds);
  }
}

void TowerManager::initialize()
{
  sf::Texture texture;
  texture.loadFromFile("img/hat.png");
  textures.push_back(texture);
  texture.loadFromFile("img/gun.png");
  textures.push_back(texture);

  Unit::Attributes attr = { 100, 100, 10, 0.5, 500 };
  std::shared_ptr<Tower> to = std::make_shared<Tower>(attr);
  to->setBodyTexture(&textures[0], 0.25);
  to->setGunTexture(&textures[1], 0.25, sf::Vector2f(-150,0));
  to->setTowerManager(this);
  to->setLocation(sf::Vector2f(400,400));
  to->initialize();
  towers.push_back(to);
}

void TowerManager::Draw(sf::RenderWindow* context)
{
  for (std::shared_ptr<Unit> to : towers)
  {
    to->draw(context);
  }
}
