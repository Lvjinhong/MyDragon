#include "AboutUI.h"

AboutUI::AboutUI()
{
	/*text.setFont(Settings::GlobalFont);
	text.setString(
		sf::String(L"C++课程设计---《戏龙珠》\n\n") +
		sf::String(L"计算机科学与技术2101\n\n") +
		sf::String(L"吕金鸿\n\n") +
		sf::String(L"郭昊\t许晨泽"));
	text.setCharacterSize(Settings::Width / 35.0f);
	text.setFillColor(sf::Color::Green);
	resetOrgin(text);
	text.setPosition(Settings::Width / 2.0, Settings::Height / 5.0 * 3.0);*/
	TextShape.setSize(sf::Vector2f(Settings::Width, Settings::Height));
	TextShape.setTexture(&AssetManager::GetTexture(Settings::BgImageFiles[5]));
	

	returnBox.updateBox(Settings::filesImages[12], 1 / 6.0f);
	returnBox.setPosition(Settings::Width / 15.0f+20, Settings::Width / 15.0f);
}

void AboutUI::processEvent(sf::RenderWindow& window)
{
	auto mousePosition = sf::Mouse::getPosition(window);
	returnBox.setFocus(false);
	if (returnBox.contain(mousePosition.x,mousePosition.y))
	{
		returnBox.setFocus(true);
		if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			GlobalGame::mouse.cd = sf::Time::Zero;
			GlobalGame::mouse.lock = true;

			GlobalGame::MainUIptr = GlobalGame::TmpUIptr;
			GlobalGame::TmpUIptr = nullptr;
			return;
		}
	}
}

void AboutUI::updateUI(sf::Time delta)
{
	//Settings::globalTitle.update(delta);
}

void AboutUI::renderUI(sf::RenderWindow& window)
{
	window.draw(TextShape);
	//Settings::globalTitle.render(window);
	returnBox.renderBox(window);

}

