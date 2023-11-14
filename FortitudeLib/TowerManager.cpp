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

  std::shared_ptr<Tower> to = std::make_shared<Tower>();
  to->setTexture(&textures[0]);
  to->setGunTexture(&textures[1]);
  to->setTowerManager(this);
  to->setDamage(10);
  to->setFireRate(2);
  to->setHealth(100);
  to->setLocation(sf::Vector2f(400,400));
  to->initialize();
  towers.push_back(to);
}

void TowerManager::Draw(sf::RenderWindow* context)
{
  for (std::shared_ptr<Tower> to : towers)
  {
    to->Draw(context);
  }
}
