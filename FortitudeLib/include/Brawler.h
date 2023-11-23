#pragma once
#include <SFML/Graphics.hpp>
#include "GameStructures.h"
#include "Tower.h"

class Brawler : public Tower
{
private:
	sf::Texture* _glassTexture;
	double _glassScale;

	sf::CircleShape _smallRangeCircle;

	double _bleedDuration;
	double _meleeRange;
	double _meleeDamage;

	std::shared_ptr<Unit> _meleeTarget;
	bool _validMeleeTarget;
	Timer _meleeTimer;
	Animation _meleeSwingAnimation;
	Animation _meleeUnswingAnimation;

public:
	Brawler(Attributes attr, sf::Texture * tex, double scale);
	void fire();
	void update(double dtAsSeconds);
	void findMeleeTarget();
	void drawRangeCircle(sf::RenderWindow* context);
	void initialize();
	void setGlassTexture(sf::Texture * tex, double scale);
	double getMeleeTargetTheta();
	double getMeleeTargetDistance();
	void meleeFire();
	double getMeleeAnimationValue();
	double getBleedDuration() { return _bleedDuration; }
	void setRangeLocation(sf::Vector2f loc);
	Animation* getUnswingAnimation() { return &_meleeUnswingAnimation; }
};