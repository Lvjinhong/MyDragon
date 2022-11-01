#include "GameUI.h"
#include "GlobalGame.h"
#include "OptionsUI.h"
#include "PauseUI.h"
#include "UserUI.h"
#include "mysql.h"
#include "MenuUI.h"
#include "UserUI.h"
#include "AboutUI.h"
GameUI::GameUI()
{
	std::cout << "GameUI初始化" << std::endl;
	gotoPause.updateBox(Settings::filesImages[8], 1 / 16.f);
	gotoPause.setPosition(
		Settings::Width / 15.0 * 14.0,
		Settings::Width / 15.0);

	PauseB = false;//记录状态，当true时表示可以暂停
	GameScoreText.setFont(Settings::GlobalFont);
	GameScore.setFont(Settings::GlobalFont);
	GameScoreText.setString(sf::String(L"分数:"));
	GameScore.setString(std::to_string(GamePlayer.getScore()));
	GameScoreText.setCharacterSize(Settings::Width / 25.0f);
	GameScore.setCharacterSize(Settings::Width / 25.0f);
	GameScoreText.setFillColor(sf::Color::Black);
	GameScore.setFillColor(sf::Color::Yellow);
	resetOrgin(GameScoreText);
	resetOrgin(GameScore);
	GameScoreText.setPosition(
		Settings::Width / 2.0f - 65,
		Settings::Width * 0.05f);
	GameScore.setPosition(
		Settings::Width / 2.0f + 48,
		Settings::Width * 0.05f);
}

void GameUI::processEvent(sf::RenderWindow& window)
{
	GamePlayer.processEvent(window);

	auto mousePosition = sf::Mouse::getPosition(window);

	//暂停功能
	gotoPause.setFocus(false);

	if (gotoPause.contain(mousePosition.x, mousePosition.y))
	{
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) PauseB = true;

		if (PauseB && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			PauseB = false;
			gotoPause.setFocus(true);
			GlobalGame::mouse.cd = sf::Time::Zero;
			GlobalGame::mouse.lock = true;
			GlobalGame::TmpGameUIptr = GlobalGame::MainUIptr;
			GlobalGame::MainUIptr = std::make_shared<PauseUI>();
		}
		return;

	}
	PauseB = false;
}

void GameUI::updateUI(sf::Time delta)
{
	while (GameThings.size() < 6)
		generateFruit();

	GamePlayer.updatePlayer(delta);
	GamePlayer.getThings(GameThings);

	if (GamePlayer.hitSelf())
	{
		GlobalGame::TmpGameUIptr = GlobalGame::MainUIptr;
		GlobalGame::MainUIptr = std::make_shared<GameOverUI>(GamePlayer.getScore());
	}

	GameScore.setString(std::to_string(GamePlayer.getScore()));
}

void GameUI::renderUI(sf::RenderWindow& window)
{
	if (Settings::GridVisibility)
		GameGrid.render(window);
	GamePlayer.renderPlayer(window);
	for (auto thing : GameThings)
		thing.renderThings(window);
	gotoPause.renderBox(window);
	window.draw(GameScore);
	window.draw(GameScoreText);
}

void GameUI::generateFruit()
{
	//初始化随机种子，保证每一次程序运行随机数都不同
	static std::default_random_engine engine(time(NULL));
	static std::default_random_engine colorEngine(time(NULL));
	//随机生成xy的位置范围
	static std::uniform_int_distribution<int> xPos(
		Settings::Width / 15.0f,
		Settings::Width -
		Settings::Width / 10.0f);

	static std::uniform_int_distribution<int> yPos(
		Settings::Width / 10.0f,
		Settings::Height -
		Settings::Width / 15.0f);

	static std::uniform_int_distribution<int> flagGet(0, 7);//0,2得分为1，其他为2
	int tem = flagGet(colorEngine);
	int score = tem <= 2 ? 1 : tem == 7 ? 3 : 2;
	GameThings.push_back(Things(
		sf::Vector2f(xPos(engine), yPos(engine)),
		tem,
		score));
}


/*-------------------------------------GameOver------------------------------------*/
GameOverUI::GameOverUI(std::size_t score)
{
	GameOverbuttons.resize(5);
	GameOverscore = score;
	GameOvertext.setFont(Settings::GlobalFont);
	GameOvertext.setString(sf::String(L"最终分数：") + std::to_string(score));
	GameOvertext.setFillColor(sf::Color::Yellow);
	GameOvertext.setCharacterSize(Settings::Width / 15);
	resetOrgin(GameOvertext);
	GameOvertext.setPosition(Settings::Width / 2.0f, Settings::Height / 4.0f);

	if (GameOverscore > GlobalGame::HistoryScore&&GlobalGame::isLogin) {
		GlobalGame::HistoryScore = GameOverscore;
	}

	GameOverbuttons[0].updateBox(Settings::filesImages[5]);
	GameOverbuttons[1].updateBox(Settings::filesImages[9]);
	GameOverbuttons[2].updateBox(Settings::filesImages[7]);
	GameOverbuttons[3].updateBox(Settings::filesImages[10]);
	GameOverbuttons[4].updateBox(Settings::filesImages[11]);

	GameOverbuttons[0].setPosition(Settings::Width / 4.0 - 50, Settings::Height / 5.0 * 3.0);
	GameOverbuttons[1].setPosition(Settings::Width / 2.0, Settings::Height / 5.0 * 3.0);
	GameOverbuttons[2].setPosition(Settings::Width / 4.0 * 3.0 + 50, Settings::Height / 5.0 * 3.0);
	GameOverbuttons[3].setPosition(Settings::Width / 4.0 + 100, Settings::Height / 5.0f * 4.0f);
	GameOverbuttons[4].setPosition(Settings::Width / 4.0 * 3.0 - 100, Settings::Height / 5.0f * 4.0f);

}

void GameOverUI::processEvent(sf::RenderWindow& window)
{
	static sf::Vector2i mousePosition;
	mousePosition = sf::Mouse::getPosition(window);

	for (auto& i : GameOverbuttons)
		i.setFocus(false);


	if (GameOverbuttons[0].contain(mousePosition.x, mousePosition.y))
	{
		GameOverbuttons[0].setFocus(true);
		if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			GlobalGame::mouse.cd = sf::Time::Zero;
			GlobalGame::mouse.lock = true;
			GlobalGame::TmpUIptr = GlobalGame::MainUIptr;
			GlobalGame::MainUIptr = std::make_shared<OptionsUI>();
			return;
		}
	}

	if (GameOverbuttons[1].contain(mousePosition.x, mousePosition.y))
	{
		GameOverbuttons[1].setFocus(true);
		if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			GlobalGame::mouse.cd = GlobalGame::mouse.clock.restart();
			GlobalGame::mouse.lock = true;
			GlobalGame::TmpGameUIptr = nullptr;
			GlobalGame::MainUIptr = std::make_shared<GameUI>();
			return;
		}
	}

	if (GameOverbuttons[2].contain(mousePosition.x, mousePosition.y))
	{
		GameOverbuttons[2].setFocus(true);
		if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			GlobalGame::mouse.cd = GlobalGame::mouse.clock.restart();
			GlobalGame::mouse.lock = true;
			GlobalGame::TmpUIptr = nullptr;
			GlobalGame::MainUIptr = std::make_shared<MenuUI>();
			return;
		}
	}

	if (GameOverbuttons[3].contain(mousePosition.x, mousePosition.y))
	{
		GameOverbuttons[3].setFocus(true);
		if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			GlobalGame::mouse.cd = sf::Time::Zero;
			GlobalGame::mouse.lock = true;
			GlobalGame::TmpUIptr = GlobalGame::MainUIptr;
			GlobalGame::MainUIptr = std::make_shared<UserUI>();
			return;
		}
	}
	if (GameOverbuttons[4].contain(mousePosition.x, mousePosition.y))
	{
		GameOverbuttons[4].setFocus(true);
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

void GameOverUI::updateUI(sf::Time delta)
{
}

void GameOverUI::renderUI(sf::RenderWindow& window)
{
	window.draw(GameOvertext);
	for (auto& button : GameOverbuttons)
		button.renderBox(window);
}
