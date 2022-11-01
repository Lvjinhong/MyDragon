#pragma once
#pragma once
#include "UI.h"
#include "Player.h"
#include "Box.h"


class GameUI :public UI
{
public:
    GameUI();

    void processEvent(sf::RenderWindow& window);
    void updateUI(sf::Time delta) ;
    void renderUI(sf::RenderWindow& window) ;

    void generateFruit();

private:
    Player GamePlayer;
    std::deque<Things> GameThings;
    Grid GameGrid;

    Box gotoPause;
    bool PauseB;

    sf::Text GameScoreText;
    sf::Text GameScore;
};
/*---------------------GameOver--------------------------------*/
class GameOverUI : public UI
{
public:
    GameOverUI(std::size_t score);

    void processEvent(sf::RenderWindow& window);
    void updateUI(sf::Time delta);
    void renderUI(sf::RenderWindow& window);

private:
    sf::Text GameOvertext;

    std::vector<Box> GameOverbuttons;
    unsigned GameOverscore;


    sf::Sound AboutSound;
};