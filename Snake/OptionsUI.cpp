#include "OptionsUI.h"

OptionsUI::OptionsUI() :
	SetNames(4), GridShowSet(2), GridColorSet(3), BgImageSet(3), beginColor(sf::Color::Green),
	GridShowfocused(-1), GridColorfocused(-1), BGImagefocused(-1), MusicTurned(-1)
{
	MusicOpened[0] = 1, MusicOpened[1] = -1;
	float characterSize = Settings::Width / 25.f;
	// init optionlist
	SetNames[0].set(
		L"网格状态：",
		Settings::GlobalFont,
		characterSize,
		beginColor,
		sf::Vector2f(Settings::Width / 5.0f, Settings::Height / 5.0f));

	SetNames[1].set(
		L"网格皮肤：",
		Settings::GlobalFont,
		characterSize,
		beginColor,
		sf::Vector2f(Settings::Width / 5.0f, Settings::Height / 5.0f * 2));

	SetNames[2].set(
		L"选择地图：",
		Settings::GlobalFont,
		characterSize,
		beginColor,
		sf::Vector2f(Settings::Width / 5.0f, Settings::Height / 5.0f * 3));
	SetNames[3].set(
		L"音乐轮播：",
		Settings::GlobalFont,
		characterSize,
		beginColor,
		sf::Vector2f(Settings::Width / 5.0f, Settings::Height / 5.0f * 4));

	GridShowSet[0].set(
		L"关闭",
		Settings::GlobalFont,
		characterSize,
		Settings::NotSeleted,
		sf::Vector2f(Settings::Width / 15.0f * 7.0f, Settings::Height / 5.0f));
	GridShowSet[1].set(
		L"开启",
		Settings::GlobalFont,
		characterSize,
		Settings::NotSeleted,
		sf::Vector2f(Settings::Width / 15.0f * 11.0f, Settings::Height / 5.0f));


	GridColorSet[0].set(
		L"飞雪",
		Settings::GlobalFont,
		characterSize,
		Settings::NotSeleted,
		sf::Vector2f(Settings::Width / 5.0f * 2.0f, Settings::Height / 5.0f * 2));
	GridColorSet[1].set(
		L"苍木",
		Settings::GlobalFont,
		characterSize,
		Settings::NotSeleted,
		sf::Vector2f(Settings::Width / 5.0f * 3.0f, Settings::Height / 5.0f * 2));
	GridColorSet[2].set(
		L"鎏金",
		Settings::GlobalFont,
		characterSize,
		Settings::NotSeleted,
		sf::Vector2f(Settings::Width / 5.0f * 4.0f, Settings::Height / 5.0f * 2));


	BgImageSet[0].set(
		L"深海废墟",
		Settings::GlobalFont,
		characterSize,
		Settings::NotSeleted,
		sf::Vector2f(Settings::Width / 5.0f * 2.0f, Settings::Height / 5.0f * 3.0f));
	BgImageSet[1].set(
		L"希望之光",
		Settings::GlobalFont,
		characterSize,
		Settings::NotSeleted,
		sf::Vector2f(Settings::Width / 5.0f * 3.0f, Settings::Height / 5.0f * 3.0f));
	BgImageSet[2].set(
		L"仰望星空",
		Settings::GlobalFont,
		characterSize,
		Settings::NotSeleted,
		sf::Vector2f(Settings::Width / 5.0f * 4.0f, Settings::Height / 5.0f * 3.0f));


	MusicOpenSet.set(L"开启",
		Settings::GlobalFont,
		characterSize,
		Settings::NotSeleted,
		sf::Vector2f(Settings::Width / 5.0f * 2.0f, Settings::Height / 5.0f * 4.0f));
	MusicTurnSet.set(L"换一首",
		Settings::GlobalFont,
		characterSize,
		Settings::NotSeleted,
		sf::Vector2f(Settings::Width / 5.0f * 3.0f, Settings::Height / 5.0f * 4.0f));

	returnBox.updateBox(Settings::filesImages[12], 1 / 6.0f);
	returnBox.setPosition(Settings::Width / 15.0f + 20, Settings::Width / 15.0f);

}
//处理事件时判定选项聚焦状态以及是否被
void OptionsUI::processEvent(sf::RenderWindow& window)
{

	auto mousePosition = sf::Mouse::getPosition(window);
	GridShowfocused = -1;
	GridColorfocused = -1;
	BGImagefocused = -1;
	MusicTurned = -1;
	MusicOpened[1] = -1;
	if (GridShowSet[0].contains(mousePosition))
	{
		GridShowfocused = 0;
		if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			Settings::GridVisibility = 0;
			return;
		}
	}
	if (GridShowSet[1].contains(mousePosition))
	{
		GridShowfocused = 1;
		if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			Settings::GridVisibility = 1;
			return;
		}
	}

	if (GridColorSet[0].contains(mousePosition))
	{
		GridColorfocused = 0;
		if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			Settings::GridColorOptions = 0;
			return;
		}
	}
	if (GridColorSet[1].contains(mousePosition))
	{
		GridColorfocused = 1;
		if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			Settings::GridColorOptions = 1;
			return;
		}
	}
	if (GridColorSet[2].contains(mousePosition))
	{
		GridColorfocused = 2;
		if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			Settings::GridColorOptions = 2;
			return;
		}
	}

	if (BgImageSet[0].contains(mousePosition))
	{
		BGImagefocused = 0;
		if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			Settings::BgIFoptions = 0;
			return;
		}
	}
	if (BgImageSet[1].contains(mousePosition))
	{
		BGImagefocused = 1;
		if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			Settings::BgIFoptions = 1;
			return;
		}
	}
	if (BgImageSet[2].contains(mousePosition))
	{
		BGImagefocused = 2;
		if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			Settings::BgIFoptions = 2;
			return;
		}
	}
	if (MusicTurnSet.contains(mousePosition)) {
		MusicTurned = 0;
		if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

			++Settings::FSound;
			GlobalGame::mouse.cd = GlobalGame::mouse.clock.restart();
			GlobalGame::mouse.lock = true;
			std::cout << "点击一次" << std::endl;
			GlobalGame::bgMusic.openFromFile(Settings::BgMusic[Settings::FSound % Settings::Sounds]);
			GlobalGame::bgMusic.setVolume(60);
			GlobalGame::bgMusic.play();
			/*GlobalGame::bgMusic.setVolume(30);
			GlobalGame::bgMusic.setLoop(true);
			*/
			return;
		}
	}

	if (MusicOpenSet.contains(mousePosition)) {
		MusicOpened[1] = 0;
		if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			GlobalGame::mouse.cd = GlobalGame::mouse.clock.restart();
			GlobalGame::mouse.lock = true;
			MusicOpened[0] = MusicOpened[0] ^ 1;
			std::cout << MusicOpened[0] << " " << 1 << std::endl;
			if (MusicOpened[0]) {
				GlobalGame::bgMusic.play();
				MusicOpenSet.getText().setString(L"开启");
			}
			else {
				GlobalGame::bgMusic.stop(); MusicOpenSet.getText().setString(L"关闭");
			}
			return;
		}
	}

	returnBox.setFocus(false);
	if (returnBox.contain(mousePosition.x, mousePosition.y))
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
/*每一次更新都进行判定，先恢复默认样式，然后将被选择的按钮着色，如果被聚焦则出现下划线
通过用变量承载下标选择项，简化了代码，模式更加统一*/
void OptionsUI::updateUI(sf::Time delta)
{
	//将选项样式恢复默认
	for (auto& i : GridShowSet)
		i.clear();

	for (auto& i : GridColorSet)
		i.clear();

	for (auto& i : BgImageSet)
		i.clear();
	MusicTurnSet.clear();
	MusicOpenSet.clear();
	GridShowSet[Settings::GridVisibility].seleted();
	if (GridShowfocused != -1)
		GridShowSet[GridShowfocused].focused();

	GridColorSet[Settings::GridColorOptions].seleted();
	if (GridColorfocused != -1)
		GridColorSet[GridColorfocused].focused();

	BgImageSet[Settings::BgIFoptions].seleted();
	if (BGImagefocused != -1)
		BgImageSet[BGImagefocused].focused();
	if (MusicTurned != -1)MusicTurnSet.focused();
	if (MusicOpened[1] != -1)MusicOpenSet.focused();

}

void OptionsUI::renderUI(sf::RenderWindow& window)
{
	if (Settings::GridVisibility)
		grid.render(window);
	for (auto& i : SetNames)
		i.render(window);
	for (auto& i : GridShowSet)
		i.render(window);
	for (auto& i : GridColorSet)
		i.render(window);
	for (auto& i : BgImageSet)
		i.render(window);
	MusicTurnSet.render(window);
	MusicOpenSet.render(window);
	returnBox.renderBox(window);
}

