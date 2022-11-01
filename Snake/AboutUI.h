#pragma once
#include "UI.h"
#include "Box.h"
class AboutUI:public UI {
public:
    AboutUI();
    void processEvent(sf::RenderWindow& window);
    void updateUI(sf::Time delta);
    void renderUI(sf::RenderWindow& window);
private:
    Box returnBox;
   // sf::Text text;
    sf::RectangleShape TextShape;
};