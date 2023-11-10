#pragma once
#include <SFML/Graphics.hpp>


class Engine;

class Leaderboard {
public:
	enum Filter {
		GLOBAL = 0,
		FRIENDS = 1,
		TIME = 2,
		WAVES = 3,
	};
private:
	Engine* engine;
	Filter people;
	Filter stat;
public:
	void init();
	Filter getPeopleFilter() { return people; }
	Filter getStatFilter() { return stat; }
	void setPeopleFilter(Filter flt) { people = flt; }
	void setStatFilter(Filter flt) { stat = flt; }
};