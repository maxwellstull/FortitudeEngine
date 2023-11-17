#include "include/TowerManager.h"
#include "include/Game.h"


void TowerManager::update(float dtAsSeconds)
{
  for (std::shared_ptr<Tower> to : towers)
  {
    to->update(dtAsSeconds);
  }
  if(isGrabbed)
  {
    grabbed->setLocation(sf::Vector2f(sf::Mouse::getPosition()));
    grabbed->setRangeLocation(sf::Vector2f(sf::Mouse::getPosition()));
  }
}

void TowerManager::initialize()
{
  sf::Texture texture;
  texture.loadFromFile("img/hat.png");
  textures.push_back(texture);
  texture.loadFromFile("img/gun.png");
  textures.push_back(texture);
  texture.loadFromFile("img/rifle.png");
  textures.push_back(texture);
  texture.loadFromFile("img/glicky.png");
  textures.push_back(texture);
  texture.loadFromFile("img/dynamite.png");
  textures.push_back(texture);
  texture.loadFromFile("img/shotgun.png");
  textures.push_back(texture);
  isGrabbed = false;
}

void TowerManager::Draw(sf::RenderWindow* context)
{
  for (std::shared_ptr<Unit> to : towers)
  {
    to->draw(context);
  }
  if (isGrabbed)
  {
    grabbed->draw(context);
    grabbed->drawRangeCircle(context);
  }
}

void TowerManager::spawnLawman()
{
  Unit::Attributes attr = { 100, 100, 10, 0.5, 500 };
  grabbed = std::make_shared<Tower>(attr);
  grabbed->setBodyTexture(&textures[0], 0.25);
  grabbed->setGunTexture(&textures[1], 0.25, sf::Vector2f(-150, 0));
  grabbed->setTowerManager(this);
  grabbed->setLocation(sf::Vector2f(sf::Mouse::getPosition()));
  grabbed->initialize();
  grabbed->pause();
  isGrabbed = true;
}

void TowerManager::spawnMarshall()
{
  Unit::Attributes attr = { 200, 200, 25, 0.5, 1000 };
  grabbed = std::make_shared<Tower>(attr);
  grabbed->setBodyTexture(&textures[0], 0.25);
  grabbed->setGunTexture(&textures[2], 0.15, sf::Vector2f(-150, -150));
  grabbed->setTowerManager(this);
  grabbed->setLocation(sf::Vector2f(sf::Mouse::getPosition()));
  grabbed->initialize();
  grabbed->pause();
  isGrabbed = true;
}

void TowerManager::spawnPistol()
{
  Unit::Attributes attr = { 50, 50, 15, 3, 350 };
  grabbed = std::make_shared<Tower>(attr);
  grabbed->setBodyTexture(&textures[0], 0.25);
  grabbed->setGunTexture(&textures[3], 0.1, sf::Vector2f(-150, -200));
  grabbed->setTowerManager(this);
  grabbed->setLocation(sf::Vector2f(sf::Mouse::getPosition()));
  grabbed->initialize();
  grabbed->pause();
  isGrabbed = true;
}

void TowerManager::spawnProspector()
{
  Unit::Attributes attr = { 300, 300, 80, 0.2, 250 };
  grabbed = std::make_shared<Tower>(attr);
  grabbed->setBodyTexture(&textures[0], 0.25);
  grabbed->setGunTexture(&textures[4], 0.1, sf::Vector2f(-150, -200));
  grabbed->setTowerManager(this);
  grabbed->setLocation(sf::Vector2f(sf::Mouse::getPosition()));
  grabbed->initialize();
  grabbed->pause();
  isGrabbed = true;
}

void TowerManager::spawnBlaster()
{
  Unit::Attributes attr = { 600, 600, 150, 1, 150 };
  grabbed = std::make_shared<Tower>(attr);
  grabbed->setBodyTexture(&textures[0], 0.25);
  grabbed->setGunTexture(&textures[5], 0.1, sf::Vector2f(-150, -200));
  grabbed->setTowerManager(this);
  grabbed->setLocation(sf::Vector2f(sf::Mouse::getPosition()));
  grabbed->initialize();
  grabbed->pause();
  isGrabbed = true;
}