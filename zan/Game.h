#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "./AssetManager.h"
class GlobalGame
{
public:

	//GlobalGame();

	/*void play();

	void handleInput();
	void update(sf::Time delta);
	void render();*/


	//static std::shared_ptr<Screen> Screen;
	//全局属性设置

private:
	sf::RenderWindow window_;
	sf::Music bgMusic_;


};