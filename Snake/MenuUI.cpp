#include "MenuUI.h"
#include "GameUI.h"
#include "OptionsUI.h"
#include "UserUI.h"
#include "AboutUI.h"
#include <Windows.h>
MenuUI::MenuUI()
{
	MenuBox.resize(5);
	MenuBox[0].updateBox(Settings::filesImages[5]);
	MenuBox[1].updateBox(Settings::filesImages[9]);
	MenuBox[2].updateBox(Settings::filesImages[7]);
	MenuBox[3].updateBox(Settings::filesImages[10]);
	MenuBox[4].updateBox(Settings::filesImages[11]);

	MenuBox[0].setPosition(Settings::Width / 4.0 - 50, Settings::Height / 5.0 * 3.0);
	MenuBox[1].setPosition(Settings::Width / 2.0, Settings::Height / 5.0 * 3.0);
	MenuBox[2].setPosition(Settings::Width / 4.0 * 3.0 + 50, Settings::Height / 5.0 * 3.0);
	MenuBox[3].setPosition(Settings::Width / 4.0 + 100, Settings::Height / 5.0f * 4.0f);
	MenuBox[4].setPosition(Settings::Width / 4.0 * 3.0 - 100, Settings::Height / 5.0f * 4.0f);

}
bool Box::contain(float x, float y)
{
	return  Box_sprite.getGlobalBounds().contains(x, y);
}
bool Box::contain(sf::Vector2f point)
{
	return  Box_sprite.getGlobalBounds().contains(point);
}
void MenuUI::processEvent(sf::RenderWindow& window)
{

	static sf::Vector2i mousePosition;
	mousePosition = sf::Mouse::getPosition(window);

	for (auto& i : MenuBox)
		i.setFocus(false);

	if (MenuBox[0].contain(mousePosition.x, mousePosition.y))
	{
		MenuBox[0].setFocus(true);
		if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			GlobalGame::mouse.cd = sf::Time::Zero;
			GlobalGame::mouse.lock = true;
			GlobalGame::TmpUIptr = GlobalGame::MainUIptr;
			GlobalGame::MainUIptr = std::make_shared<OptionsUI>();
			return;
		}
	}

	if (MenuBox[1].contain(mousePosition.x, mousePosition.y))
	{
		MenuBox[1].setFocus(true);
		if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			GlobalGame::mouse.lock = true;
			GlobalGame::mouse.cd = sf::Time::Zero;
			GlobalGame::MainUIptr = std::make_shared<GameUI>();
			return;
		}

	}
	if (MenuBox[2].contain(mousePosition.x, mousePosition.y))
	{
		MenuBox[2].setFocus(true);
		if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			window.close();
			return;
		}
	}
	if (MenuBox[3].contain(mousePosition.x, mousePosition.y))
	{
		MenuBox[3].setFocus(true);
		if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			GlobalGame::mouse.cd = sf::Time::Zero;
			GlobalGame::mouse.lock = true;
			GlobalGame::TmpUIptr = GlobalGame::MainUIptr;
			GlobalGame::MainUIptr = std::make_shared<UserUI>();
			return;
		}
	}
	if (MenuBox[4].contain(mousePosition.x, mousePosition.y))
	{
		MenuBox[4].setFocus(true);
		if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			AboutSound.setBuffer(AssetManager::GetSoundBuffer(Settings::filesSounds[3]));
			AboutSound.setVolume(50);
			AboutSound.play();
			GlobalGame::mouse.cd = sf::Time::Zero;
			GlobalGame::mouse.lock = true;
			GlobalGame::TmpUIptr = GlobalGame::MainUIptr;
			GlobalGame::MainUIptr = std::make_shared<AboutUI>();
			return;
		}
	}

}

void MenuUI::updateUI(sf::Time delta)
{
	Settings::globalTitle->update(delta);
}

void MenuUI::renderUI(sf::RenderWindow& window)
{

	for (auto& button : MenuBox)
		button.renderBox(window);
	Settings::globalTitle->render(window);
}
