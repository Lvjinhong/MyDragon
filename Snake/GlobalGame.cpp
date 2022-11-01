#include "./GlobalGame.h"
#include "AssetManager.h"
#include "GameUI.h"
#include "MenuUI.h"
#include "OptionsUI.h"
#include "UserUI.h"
GlobalGame::GlobalGame()
{
	GlobalGame::MainUIptr = std::make_shared<MenuUI>();
	//GlobalGame::UserUIptr = std::make_shared<UserUI>();
	Settings::globalTitle = std::make_shared<GlobalTitle>();
	Settings::GlobalFont = AssetManager::GetFont("Fonts/10014.ttf");
	//设置采样率为8，抗锯齿
	sf::ContextSettings context_setting;
	context_setting.antialiasingLevel = 8;

	//初始化窗口设置
	window.create(
		Settings::GlobalVideoMode,   // videoMode
		"MyDragon",      // window name
		sf::Style::Default, context_setting); // window Style
	sf::Image icon;
	icon.loadFromFile("Image/favoin.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	bgMusic.openFromFile(Settings::BgMusic[0]);
	bgMusic.setVolume(30);
	bgMusic.setLoop(true);
	bgMusic.play();

	std::cout << "GlobalGame初始化完毕" << std::endl;
}

Check::Check() {
	clock = sf::Clock();
	cd = sf::Time();
	lock = false;
}
void Check::work() {
	sf::Time delta = clock.restart();
	cd += delta;
	if (cd.asSeconds() > 0.5f)
	{
		cd -= sf::seconds(0.5f);
		lock = false;
	}
}
std::shared_ptr<UI> GlobalGame::UserUIptr = nullptr;
std::shared_ptr<UI> GlobalGame::MainUIptr = nullptr;
std::shared_ptr<UI> GlobalGame::TmpUIptr = nullptr;
std::shared_ptr<UI> GlobalGame::TmpGameUIptr = nullptr;
Check GlobalGame::mouse = Check();
Check GlobalGame::keyboard = Check();

bool GlobalGame::isLogin = false;
std::string GlobalGame::MyUsername("Please Login");
sf::String GlobalGame::MyPassword;
int GlobalGame::HistoryScore = 0;

sf::Music GlobalGame::bgMusic = sf::Music();

void GlobalGame::play()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	GlobalGame::mouse.clock.restart();
	GlobalGame::keyboard.clock.restart();

	/*自上一次游戏循环过去了一定量的真实时间（CPU时钟）, 则需要为游戏内时间进行相应的推进，
	以追上玩家的时间，保证游戏进度相同。 我们使用一系列的固定时间步长*/
	while (window.isOpen())
	{
		sf::Time delta = clock.restart();
		timeSinceLastUpdate += delta;

		while (timeSinceLastUpdate > Settings::TimePerFrame)
		{
			timeSinceLastUpdate -= Settings::TimePerFrame;
			ProcessEvent();

			update(Settings::TimePerFrame);

			//render();
		}
		render();
		GlobalGame::mouse.work();
		GlobalGame::keyboard.work();

	}
}

void GlobalGame::ProcessEvent()
{//定义局部静态变量，减少多次频繁定义销毁造成的IO开销
	static sf::Event event;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}

	if (window.hasFocus() &&
		sf::FloatRect(
			sf::Vector2f(0, 0),
			sf::Vector2f(
				Settings::Width,
				Settings::Height))
		.contains(static_cast<sf::Vector2f>(
			sf::Mouse::getPosition(window))))
		GlobalGame::MainUIptr->processEvent(window);
}

void GlobalGame::update(sf::Time delta)
{//传到主窗口进行更新
	GlobalGame::MainUIptr->updateUI(delta);
}


void GlobalGame::render()
{//主窗口渲染
	//window.clear(sf::Color::White);
	sf::RectangleShape Bgshape;
	Bgshape.setSize(sf::Vector2f(Settings::Width, Settings::Height));
	Bgshape.setTexture(&AssetManager::GetTexture(Settings::BgImageFiles[Settings::BgIFoptions]));
	window.draw(Bgshape);
	GlobalGame::MainUIptr->renderUI(window);
	window.display();
}


