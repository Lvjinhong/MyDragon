#pragma once
#include "UI.h"
#include "Box.h"
class PauseUI :public UI {
public:
	PauseUI();
	 void processEvent(sf::RenderWindow& window);
	 void updateUI(sf::Time delta);
	 void renderUI(sf::RenderWindow& window);
private:
	 std::vector<Box> PauseBox;
	 Box returnBox;
	 sf::Sound AboutSound;
};