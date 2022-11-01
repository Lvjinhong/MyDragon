#include "GlobalTitle.h"
#include "./GlobalGame.h"
GlobalTitle::GlobalTitle()
{
	titleTexture = AssetManager::GetTexture(Settings::BgImageFiles[4]);
	std::cout<<"logo初始化成功" << std::endl;
	titleTexture.setSmooth(true);
	titleSprite.setTexture(titleTexture);

	sf::FloatRect titleSpriteBounds = resetOrgin(titleSprite);
	titleSprite.setScale( Settings::Width/ titleSpriteBounds.width * 0.5f, Settings::Width / titleSpriteBounds.width * 0.5f);
	titleSprite.setPosition(Settings::Width / 2, Settings::Height / 4);
}

void GlobalTitle::update(sf::Time delta)
{
	if (rotateDirection)//顺时针旋转
	{
		titleSprite.rotate(delta.asSeconds());
		if (titleSprite.getRotation() >= 10.0f && titleSprite.getRotation() <= 11.0f)
			rotateDirection = false;
	}
	else
	{
		titleSprite.rotate(-delta.asSeconds());
		if (titleSprite.getRotation() >= 349.0f && titleSprite.getRotation() <= 350.0f)
			rotateDirection = true;
	}
}



void GlobalTitle::render(sf::RenderWindow& window)
{
	window.draw(titleSprite);

}
