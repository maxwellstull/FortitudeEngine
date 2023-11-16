#include "include/Unit.h"

void Unit::update(double dt)
{
  _gunFireAnimation.update(dt);
  _gunRecoilAnimation.update(dt);
  fireTimer.update(dt);
}

void Unit::draw(sf::RenderWindow* context)
{
  if (_active)
  {
    if (_healthBar)
    {
      context->draw(_maxHealthBar);
      context->draw(_curHealthBar);
    }
    context->draw(_bodySpr);
    context->draw(_gunSpr);
  }
}

void Unit::setBodyTexture(sf::Texture* texture, double scale)
{
  _bodyTexture = texture;
  _bodySpr.setTexture(*_bodyTexture);
  _bodySpr.setScale(scale, scale);
}

void Unit::setGunTexture(sf::Texture* texture, double scale, sf::Vector2f offset)
{
  _gunTexture = texture;
  _gunSpr.setTexture(*_gunTexture);
  _gunSpr.setScale(scale, scale);
  sf::FloatRect bds = _gunSpr.getLocalBounds();
  _gunSpr.setOrigin(bds.left + (bds.width / 2.f) + offset.x, bds.top + (bds.height / 2.f) + offset.y);
}

void Unit::initialize(bool showHealthBar)
{
  _healthBar = showHealthBar;
  if (_healthBar)
  {
    _maxHealthBar = sf::RectangleShape(sf::Vector2f(30, 5));
    sf::FloatRect bds = _maxHealthBar.getLocalBounds();
    _maxHealthBar.setOrigin(bds.left + (bds.width / 2.f), bds.top + (bds.height / 2.f));
    _maxHealthBar.setFillColor(sf::Color::Red);

    _curHealthBar = sf::RectangleShape(sf::Vector2f(30, 5));
    bds = _curHealthBar.getLocalBounds();
    _curHealthBar.setOrigin(bds.left + (bds.width / 2.f), bds.top + (bds.height / 2.f));
    _curHealthBar.setFillColor(sf::Color::Green);

    _maxHealthBar.setPosition(getLocation() + sf::Vector2f(0, 25));
    _curHealthBar.setPosition(getLocation() + sf::Vector2f(0, 25));
  }

  _gunFireAnimation = Animation(0, 45, (1.f / _attributes.fireRate) / 3);
  _gunRecoilAnimation = Animation(45, 0, (1.f / _attributes.fireRate) / 2);
  activate();
}

void Unit::findTarget(std::vector<std::shared_ptr<Unit>> ops)
{
  double min_distance = INFINITY;
  double distance;
  double theta;
  double xd;
  double yd;

  for (auto op : ops)
  {
    if (op->isActive())
    {
      xd = op->getLocation().x - getLocation().x;
      yd = op->getLocation().y - getLocation().y;
      theta = atan2(yd, xd);

      distance = computeDistance(xd, yd);
      if (distance < getAttributes().range && distance < min_distance)
      {
        min_distance = distance;
        target = op;
        validTarget = true;
      }
    }
  }
}

double Unit::getAnimationValue()
{
  double retVal = 0;
  if (_gunFireAnimation.isActive())
  {
    retVal = _gunFireAnimation.get();
  }
  else if (_gunRecoilAnimation.isActive())
  {
    retVal = _gunRecoilAnimation.get();
  }
  return retVal;
}
