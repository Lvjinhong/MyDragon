#pragma once
#include "resource.h"
#include "UI.h"
#include "Box.h"
class MenuUI : public UI
{
public:
    MenuUI();
    void processEvent(sf::RenderWindow& window);
        void updateUI(sf::Time delta);
        void renderUI(sf::RenderWindow& window);
  

private:
    std::vector<Box> MenuBox;
    //setBox gotoUser;
    //setBox gotoAbout;
    sf::Sound AboutSound;
};