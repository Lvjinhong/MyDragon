#pragma once
#include "resource.h"
#include "UI.h"
#include "UserUI.h"
class rankUI :public UI {
public:
	rankUI();
	rankUI(vector<ranks>& Rank);
	void processEvent(sf::RenderWindow& window);
	void updateUI(sf::Time delta);
	void renderUI(sf::RenderWindow& window);

};