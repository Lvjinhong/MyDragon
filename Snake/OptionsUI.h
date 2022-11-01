#pragma once
#include "UI.h"
#include "Box.h"
class OptionsUI:public UI {
public:
    OptionsUI();
    void processEvent(sf::RenderWindow& window);
    void updateUI(sf::Time delta);
    void renderUI(sf::RenderWindow& window);

private:
    sf::Color beginColor;
    std::vector<setBox> SetNames;
    std::vector<setBox> GridShowSet;
    std::vector<setBox> GridColorSet;
    std::vector<setBox> BgImageSet;
    setBox MusicTurnSet;
    setBox MusicOpenSet;
    int GridShowfocused;
    int GridColorfocused;
    int BGImagefocused;
    int MusicTurned;
    int MusicOpened[2];//���ص��л����۽�״̬�ĸı�
    Grid grid;

    Box returnBox;
};