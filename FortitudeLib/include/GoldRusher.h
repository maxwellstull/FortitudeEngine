#pragma once
#include <SFML/Graphics.hpp>
#include "GameStructures.h"
#include "Enemy.h"

class GoldRusher : public Enemy
{
private:
//	double _meleeRange;
//	double _meleeDamage;

//	std::shared_ptr<Unit> _meleeTarget;
//	bool _validMeleeTarget;
//	Timer _meleeTimer;
	Animation _meleeSwingAnimation;
	Animation _meleeUnswingAnimation;
public:
	GoldRusher(Attributes attr);
	void update(float dtAsSeconds);
//	void findTarget();
//	void findMeleeTarget();
	void initialize(PathSegment * st);
	double getMeleeTargetTheta();
	double getMeleeTargetDistance();
	void meleeFire();
	void fire();
	double getMeleeAnimationValue();
	double getAnimationValue();
	Animation* getUnswingAnimation() { return &_meleeUnswingAnimation; }
};