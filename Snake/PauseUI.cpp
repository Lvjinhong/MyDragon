#include "PauseUI.h"
#include "UserUI.h"
#include "AboutUI.h"
#include "OptionsUI.h"
#include "GameUI.h"
#include "MenuUI.h"
PauseUI::PauseUI():PauseBox(5)
{//初始化各种按钮样式
    PauseBox[0].updateBox(Settings::filesImages[5]);
    PauseBox[1].updateBox(Settings::filesImages[6]);
    PauseBox[2].updateBox(Settings::filesImages[7]);
    PauseBox[3].updateBox(Settings::filesImages[10]);
    PauseBox[4].updateBox(Settings::filesImages[11]);


    returnBox.updateBox(Settings::filesImages[12], 1 / 6.0f);

    /*PauseBox[0].setPosition(Settings::Width / 3.0, Settings::Height/ 5.0 * 3.0);
    PauseBox[1].setPosition(Settings::Width / 2.0, Settings::Height/ 5.0 * 3.0);
    PauseBox[2].setPosition(Settings::Width / 3.0 * 2.0, Settings::Height/ 5.0 * 3.0);*/
    PauseBox[0].setPosition(Settings::Width / 4.0 - 50, Settings::Height / 5.0 * 3.0);
    PauseBox[1].setPosition(Settings::Width / 2.0, Settings::Height / 5.0 * 3.0);
    PauseBox[2].setPosition(Settings::Width / 4.0 * 3.0 + 50, Settings::Height / 5.0 * 3.0);
    PauseBox[3].setPosition(Settings::Width / 4.0 + 100, Settings::Height / 5.0f * 4.0f);
    PauseBox[4].setPosition(Settings::Width / 4.0 * 3.0 - 100, Settings::Height / 5.0f * 4.0f);
    
    returnBox.setPosition(Settings::Width / 15.0+20, Settings::Width / 15.0);

}
void PauseUI::processEvent(sf::RenderWindow& window) {
    //初始化设置
    auto mousePosition = sf::Mouse::getPosition(window);
    for (auto& i : PauseBox)
        i.setFocus(false);
    returnBox.setFocus(false);

    if (PauseBox[0].contain(mousePosition.x, mousePosition.y))
    {
        PauseBox[0].setFocus(true);
        if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            GlobalGame::mouse.cd = sf::Time::Zero;
            GlobalGame::mouse.lock = true;
            GlobalGame::TmpUIptr = GlobalGame::MainUIptr;
            GlobalGame::MainUIptr = std::make_shared<OptionsUI>();
            return;
        }
    }

    if (PauseBox[1].contain(mousePosition.x, mousePosition.y))
    {
        PauseBox[1].setFocus(true);
        if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            GlobalGame::mouse.cd = GlobalGame::mouse.clock.restart();
            GlobalGame::mouse.lock = true;
            GlobalGame::MainUIptr = GlobalGame::TmpGameUIptr;
            return;
        }
    }

    if (PauseBox[2].contain(mousePosition.x, mousePosition.y))
    {
        PauseBox[2].setFocus(true);
        if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            GlobalGame::mouse.cd = GlobalGame::mouse.clock.restart();
            GlobalGame::mouse.lock = true;
            GlobalGame::TmpUIptr = nullptr;
            GlobalGame::MainUIptr = std::make_shared<MenuUI>();
            
        }
        return;
    }

    if (returnBox.contain(mousePosition.x, mousePosition.y))
    {
        returnBox.setFocus(true);
        if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            GlobalGame::mouse.cd = GlobalGame ::mouse.clock.restart();
            GlobalGame::mouse.lock = true;
            GlobalGame ::MainUIptr = GlobalGame::TmpGameUIptr;
            GlobalGame::TmpGameUIptr = nullptr;
            return;
        }
    }
    if (PauseBox[3].contain(mousePosition.x, mousePosition.y))
    {
        PauseBox[3].setFocus(true);
        if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            GlobalGame::mouse.cd = sf::Time::Zero;
            GlobalGame::mouse.lock = true;
            GlobalGame::TmpUIptr = GlobalGame::MainUIptr;
            GlobalGame::MainUIptr = std::make_shared<UserUI>();
            return;
        }
    }
    if (PauseBox[4].contain(mousePosition.x, mousePosition.y))
    {
        PauseBox[4].setFocus(true);
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

void PauseUI::updateUI(sf::Time delta)
{
    Settings::globalTitle->update(delta);
}

void PauseUI::renderUI(sf::RenderWindow& window)
{
    //当游戏暂停时，贪吃蛇的画面不会变
    GlobalGame::TmpGameUIptr->renderUI(window);
    Settings::globalTitle->render(window);
    for (auto& button : PauseBox)
    {
        button.renderBox(window);
    }
    returnBox.renderBox(window);
 
    
}



