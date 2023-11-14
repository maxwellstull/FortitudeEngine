#include "include/Game.h"

void Game::update(float dtAsSeconds)
{
	if(isActive)
	{
		enm.update(dtAsSeconds);
	}
}

void Game::updateHealthHUD()
{
	std::string dollabills = std::to_string(state.currentHealth) + "/" + std::to_string(state.maxHealth);
	healthHUD.setString(dollabills);
}

void Game::load()
{
	enm.setGame(this);
	enm.initialize(info);

	font.loadFromFile("img/cowboy.ttf");
	moneyTex.loadFromFile("img/moneybag.png");
	moneySpr.setTexture(moneyTex);
	sf::FloatRect bds = moneySpr.getLocalBounds();
	moneySpr.setOrigin(bds.left + (bds.width / 2.f), bds.top + (bds.height / 2.f));
	moneySpr.setScale(0.2, 0.2);

	state.maxHealth = 100;
	state.currentHealth = 100;

	
	updateHealthHUD();
	healthHUD.setFont(font);
	healthHUD.setCharacterSize(48);
	bds = healthHUD.getLocalBounds();
	healthHUD.setOrigin(bds.left + (bds.width / 2.f), bds.top + (bds.height / 2.f));


	healthHUD.setPosition(200, 50);
	moneySpr.setPosition(300, 50);


	activate();
}

void Game::Draw(sf::RenderWindow* context)
{
	activeMap->Draw(context);
	enm.Draw(context);

	context->draw(moneySpr);
	context->draw(healthHUD);
}