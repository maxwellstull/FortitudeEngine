#include "include/Game.h"

void Game::update(float dtAsSeconds)
{
	if(isActive)
	{
		enm.update(dtAsSeconds);
		twm.update(dtAsSeconds);
	}
}

void Game::updateHealthHUD()
{
	std::string dollabills = std::to_string(state.currentHealth) + "/" + std::to_string(state.maxHealth);
	healthHUD.setString(dollabills);
}

void Game::updateWaveHUD()
{
	std::string waves = std::to_string(state.currentWave) + "/" + std::to_string(info.MaxWaves);
	waveHUD.setString(waves);
}

void Game::hitvisit(sf::Vector2f cursorPos)
{
	if (isActive)
	{
		twm.hitvisit(cursorPos);
	}
}

void Game::load()
{
	enm.setGame(this);
	enm.initialize(info);
	twm.setGame(this);
	twm.initialize();

	state.maxHealth = 100;
	state.currentHealth = 100;
	state.currentWave = 1;


	font.loadFromFile("img/cowboy.ttf");
	moneyTex.loadFromFile("img/moneybag.png");
	moneySpr.setTexture(moneyTex);
	sf::FloatRect bds = moneySpr.getLocalBounds();
	moneySpr.setOrigin(bds.left + (bds.width / 2.f), bds.top + (bds.height / 2.f));
	moneySpr.setScale(0.2, 0.2);
	waveTex.loadFromFile("img/3men.png");
	waveSpr.setTexture(waveTex);
	bds = waveSpr.getLocalBounds();
	waveSpr.setOrigin(bds.left + (bds.width / 2.f), bds.top + (bds.height / 2.f));
	waveSpr.setScale(0.2, 0.2);

	
	healthHUD.setFont(font);
	healthHUD.setCharacterSize(48);
	updateHealthHUD();
	bds = healthHUD.getLocalBounds();
	healthHUD.setOrigin(bds.left + (bds.width / 2.f), bds.top + (bds.height / 2.f));
		

	waveHUD.setFont(font);
	waveHUD.setCharacterSize(48);
	updateWaveHUD();

	bds = waveHUD.getLocalBounds();
	waveHUD.setOrigin(bds.left + (bds.width / 2.f), bds.top + (bds.height / 2.f));

	healthHUD.setPosition(300, 50);
	moneySpr.setPosition(200, 50);
	waveHUD.setPosition(500, 50);
	waveSpr.setPosition(420, 50);





	activate();
}

void Game::Draw(sf::RenderWindow* context)
{
	activeMap->Draw(context);
	enm.Draw(context);
	twm.Draw(context);

	context->draw(moneySpr);
	context->draw(healthHUD);
	context->draw(waveHUD);
	context->draw(waveSpr);
}