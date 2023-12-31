#include "include/TowerManager.h"
#include "include/Game.h"
#include "include/Blaster.h"
#include "include/Prospector.h"
#include "include/Lawman.h"
#include "include/Marshall.h"
#include "include/Repeater.h"
#include "include/Brawler.h"
#include "include/Doc.h"
#include "include/Sheriff.h"


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
  if (splashActive)
  {
    selectedSplash.refresh();
//    selectedSplash.update(dtAsSeconds);
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
  texture.loadFromFile("img/bullet.png");
  textures.push_back(texture);
  texture.loadFromFile("img/pocketsand.png");
  textures.push_back(texture);
  texture.loadFromFile("img/brokenglass.png");
  textures.push_back(texture);
  texture.loadFromFile("img/needle.png");
  textures.push_back(texture);
  isGrabbed = false;
  splashActive = false;
  selectedSplash.init();
  selectedSplash.SetEngine(getGame()->GetEngine());
}

void TowerManager::Draw(sf::RenderWindow* context)
{
  for (std::shared_ptr<Tower> to : towers)
  {
    to->draw(context);
  }
  if (isGrabbed)
  {
    grabbed->draw(context);
    //grabbed->drawRangeCircle(context);
  }
  if (splashActive)
  {
    selectedSplash.Draw(context);
  }
}

void TowerManager::spawnLawman()
{
  Unit::Attributes attr = { 
    100,  //current health
    10,   //damage
    0.75,  // fire rate
    300,  // range (in pixels)
    75,   //accuracy (0 to 100)
    400,   //projectile speed
    0, //armor
  };
  Tower::AmmoInfo ami = { 6, 0};
  grabbed = std::make_shared<Lawman>(attr);
  grabbed->setBodyTexture(&textures[0], 0.25);
  grabbed->setGunTexture(&textures[1], 0.25, sf::Vector2f(-150, 0));
  grabbed->setProjTexture(&textures[6], 0.25);
  grabbed->setAmmoInfo(ami);
  grabbed->setTowerManager(this);
  grabbed->setLocation(sf::Vector2f(sf::Mouse::getPosition()));
  grabbed->initialize();
  grabbed->pause();
  grabbed->setDrawRange();
  isGrabbed = true;
}

void TowerManager::spawnMarshall()
{
  Unit::Attributes attr = {
    50,  //current health
    25,   //damage
    0.5,  // fire rate
    500,  // range (in pixels)
    75,   //accuracy (0 to 100)
    400,   //projectile speed
    0, //armor
  };
  Tower::AmmoInfo ami = { 8, 0.2 };
  grabbed = std::make_shared<Marshall>(attr);
  grabbed->setBodyTexture(&textures[0], 0.25);
  grabbed->setGunTexture(&textures[2], 0.15, sf::Vector2f(-150, -150));
  grabbed->setProjTexture(&textures[6], 0.25);
  grabbed->setAmmoInfo(ami);
  grabbed->setTowerManager(this);
  grabbed->setLocation(sf::Vector2f(sf::Mouse::getPosition()));
  grabbed->initialize();
  grabbed->pause();
  grabbed->setDrawRange();
  isGrabbed = true;
}

void TowerManager::spawnRepeater()
{
  Unit::Attributes attr = {
    50,  //current health
    8,   //damage
    3,  // fire rate
    350,  // range (in pixels)
    75,   //accuracy (0 to 100)
    400,   //projectile speed
    0, //armor
  };
  Tower::AmmoInfo ami = { 15, 0 };
  grabbed = std::make_shared<Repeater>(attr, &textures[7], 0.25);
  grabbed->setBodyTexture(&textures[0], 0.25);
  grabbed->setGunTexture(&textures[3], 0.1, sf::Vector2f(-150, -200));
  grabbed->setProjTexture(&textures[6], 0.25);
  grabbed->setAmmoInfo(ami);
  grabbed->setTowerManager(this);
  grabbed->setLocation(sf::Vector2f(sf::Mouse::getPosition()));
  grabbed->initialize();
  grabbed->pause();
  grabbed->setDrawRange();
  isGrabbed = true;
}

void TowerManager::spawnProspector()
{
  Unit::Attributes attr = {
    200,  //current health
    80,   //damage
    0.5,  // fire rate
    400,  // range (in pixels)
    75,   //accuracy (0 to 100)
    400,   //projectile speed
    0, //armor
  };
  Tower::AmmoInfo ami = { 2, 0 };
  grabbed = std::make_shared<Prospector>(attr);
  grabbed->setBodyTexture(&textures[0], 0.25);
  grabbed->setGunTexture(&textures[4], 0.1, sf::Vector2f(-150, -200));
  grabbed->setProjTexture(&textures[4], 0.1);
  grabbed->setAmmoInfo(ami);
  grabbed->setTowerManager(this);
  grabbed->setLocation(sf::Vector2f(sf::Mouse::getPosition()));
  grabbed->initialize();
  grabbed->pause();
  grabbed->setDrawRange();
  isGrabbed = true;
}

void TowerManager::spawnBlaster()
{
  Unit::Attributes attr = {
    300,  //current health
    20,   //damage
    1,  // fire rate
    100,  // range (in pixels)
    75,   //accuracy (0 to 100)
    400,   //projectile speed
    0, //armor
  };
  Tower::AmmoInfo ami = { 4, 0 };
  grabbed = std::make_shared<Blaster>(attr);
  grabbed->setBodyTexture(&textures[0], 0.25);
  grabbed->setGunTexture(&textures[5], 0.1, sf::Vector2f(-150, -200));
  grabbed->setProjTexture(&textures[6], 0.25);
  grabbed->setAmmoInfo(ami);
  grabbed->setTowerManager(this);
  grabbed->setLocation(sf::Vector2f(sf::Mouse::getPosition()));
  grabbed->initialize();
  grabbed->pause();
  grabbed->setDrawRange();
  isGrabbed = true;
}

void TowerManager::spawnBrawler()
{
    Unit::Attributes attr = {
    300,  //current health
    20,   //damage
    1,  // fire rate
    300,  // range (in pixels)
    75,   //accuracy (0 to 100)
    400,   //projectile speed
    0, //armor
    };
    Tower::AmmoInfo ami = { 2, 0 };
    grabbed = std::make_shared<Brawler>(attr, &textures[8], 0.25);
    grabbed->setBodyTexture(&textures[0], 0.25);
    grabbed->setGunTexture(&textures[8], 0.25, sf::Vector2f(-150, 0));
    grabbed->setProjTexture(&textures[8], 0.25);
    grabbed->setAmmoInfo(ami);
    grabbed->setTowerManager(this);
    grabbed->setLocation(sf::Vector2f(sf::Mouse::getPosition()));
    grabbed->initialize();
    grabbed->pause();
    grabbed->setDrawRange();
    isGrabbed = true;
}

void TowerManager::spawnDoc()
{
    Unit::Attributes attr = {
    100,  //current health
    5,   //damage
    0.5,  // fire rate
    100,  // range (in pixels)
    75,   //accuracy (0 to 100)
    400,   //projectile speed
    0, //armor
    };
    Tower::AmmoInfo ami = { 1, 0 };
    grabbed = std::make_shared<Doc>(attr);
    grabbed->setBodyTexture(&textures[0], 0.25);
    grabbed->setGunTexture(&textures[9], 0.25, sf::Vector2f(-150, 0));
    grabbed->setProjTexture(&textures[9], 0.25);
    grabbed->setAmmoInfo(ami);
    grabbed->setTowerManager(this);
    grabbed->setLocation(sf::Vector2f(sf::Mouse::getPosition()));
    grabbed->initialize();
    grabbed->pause();
    grabbed->setDrawRange();
    isGrabbed = true;
}

void TowerManager::spawnSheriff()
{
  Unit::Attributes attr = {
    500,  //current health
    10,   //damage
    0.75,  // fire rate
    400,  // range (in pixels)
    75,   //accuracy (0 to 100)
    400,   //projectile speed
    0, //armor
  };
  Tower::AmmoInfo ami = { 12, 12 };
  grabbed = std::make_shared<Sheriff>(attr);
  grabbed->setBodyTexture(&textures[0], 0.25);
  grabbed->setGunTexture(&textures[1], 0.25, sf::Vector2f(-150, 0));
  grabbed->setProjTexture(&textures[6], 0.25);
  grabbed->setAmmoInfo(ami);
  grabbed->setTowerManager(this);
  grabbed->setLocation(sf::Vector2f(sf::Mouse::getPosition()));
  grabbed->initialize();
  grabbed->pause();
  grabbed->setDrawRange();
  isGrabbed = true;
}


void TowerManager::hitvisit(sf::Vector2f cursorPos)
{
  if(splashedTower)
  {
    splashedTower->clearDrawRange();
  }
  selectedSplash.deactivate();
  splashActive = false;
  splashedTower = nullptr;
  for (std::shared_ptr<Tower> to : towers)
  {
    if (to->hittest(cursorPos))
    {
      if (to->isPaused() == false);
      {
        selectedSplash.TowerSplash(to);
        splashedTower = to;
        splashedTower->setDrawRange();
        splashedTower->setRangeLocation(splashedTower->getLocation());
        splashActive = true;
        break;
      }  
    }
  }
}
