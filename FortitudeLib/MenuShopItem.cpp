#include "include/MenuShopItem.h"

MenuShopItem::MenuShopItem(const char* label, const char* fontName, sf::IntRect boundaryRect, int textSize, sf::Texture* texture, sf::Vector2f textOffset)
 : MenuComponent(label, fontName, sf::Vector2f(boundaryRect.left + textOffset.x, boundaryRect.top + textOffset.y), textSize)
{
	text = texture;
	spr.setTexture(*text);
	sf::FloatRect bds = spr.getLocalBounds();
	spr.setOrigin(bds.left + (bds.width / 2.f), bds.top + (bds.height / 2.f));
	spr.setPosition(boundaryRect.left + boundaryRect.width / 2.f, boundaryRect.top + boundaryRect.height / 2.f);

	backdrop = sf::RectangleShape(sf::Vector2f(boundaryRect.width, boundaryRect.height));
	backdrop.setOrigin((backdrop.getPosition().x / 2.0f), (backdrop.getPosition().x / 2.0f));
	backdrop.setOutlineColor(sf::Color::Black);
	backdrop.setOutlineThickness(10);
	backdrop.setPosition(boundaryRect.left, boundaryRect.top);

}


void MenuShopItem::Draw(sf::RenderWindow* context)
{
	context->draw(backdrop);
	context->draw(spr);
	MenuComponent::Draw(context);
}

void MenuShopItem::Update(float dtAsSeconds)
{
	MenuComponent::Update(dtAsSeconds);
}

bool MenuShopItem::hittest(sf::Vector2f cursorPos)
{
	sf::FloatRect bounds = backdrop.getGlobalBounds();
	return bounds.contains(cursorPos) || MenuComponent::hittest(cursorPos);
}


void MenuShopItem::setFillColor(sf::Color c)
{
	backdrop.setFillColor(c);
}
void MenuShopItem::setSpriteScale(double x, double y)
{
	spr.setScale(x, y);
}
void MenuShopItem::setSpriteRotation(double rot)
{
	spr.setRotation(rot);
}