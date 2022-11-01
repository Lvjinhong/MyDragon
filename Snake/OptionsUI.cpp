#include "OptionsUI.h"

OptionsUI::OptionsUI() :
	SetNames(4), GridShowSet(2), GridColorSet(3), BgImageSet(3), beginColor(sf::Color::Green),
	GridShowfocused(-1), GridColorfocused(-1), BGImagefocused(-1), MusicTurned(-1)
{
	MusicOpened[0] = 1, MusicOpened[1] = -1;
	float characterSize = Settings::Width / 25.f;
	// init optionlist
	SetNames[0].set(
		L"����״̬��",
		Settings::GlobalFont,
		characterSize,
		beginColor,
		sf::Vector2f(Settings::Width / 5.0f, Settings::Height / 5.0f));

	SetNames[1].set(
		L"����Ƥ����",
		Settings::GlobalFont,
		characterSize,
		beginColor,
		sf::Vector2f(Settings::Width / 5.0f, Settings::Height / 5.0f * 2));

	SetNames[2].set(
		L"ѡ���ͼ��",
		Settings::GlobalFont,
		characterSize,
		beginColor,
		sf::Vector2f(Settings::Width / 5.0f, Settings::Height / 5.0f * 3));
	SetNames[3].set(
		L"�����ֲ���",
		Settings::GlobalFont,
		characterSize,
		beginColor,
		sf::Vector2f(Settings::Width / 5.0f, Settings::Height / 5.0f * 4));

	GridShowSet[0].set(
		L"�ر�",
		Settings::GlobalFont,
		characterSize,
		Settings::NotSeleted,
		sf::Vector2f(Settings::Width / 15.0f * 7.0f, Settings::Height / 5.0f));
	GridShowSet[1].set(
		L"����",
		Settings::GlobalFont,
		characterSize,
		Settings::NotSeleted,
		sf::Vector2f(Settings::Width / 15.0f * 11.0f, Settings::Height / 5.0f));


	GridColorSet[0].set(
		L"��ѩ",
		Settings::GlobalFont,
		characterSize,
		Settings::NotSeleted,
		sf::Vector2f(Settings::Width / 5.0f * 2.0f, Settings::Height / 5.0f * 2));
	GridColorSet[1].set(
		L"��ľ",
		Settings::GlobalFont,
		characterSize,
		Settings::NotSeleted,
		sf::Vector2f(Settings::Width / 5.0f * 3.0f, Settings::Height / 5.0f * 2));
	GridColorSet[2].set(
		L"�̽�",
		Settings::GlobalFont,
		characterSize,
		Settings::NotSeleted,
		sf::Vector2f(Settings::Width / 5.0f * 4.0f, Settings::Height / 5.0f * 2));


	BgImageSet[0].set(
		L"�����",
		Settings::GlobalFont,
		characterSize,
		Settings::NotSeleted,
		sf::Vector2f(Settings::Width / 5.0f * 2.0f, Settings::Height / 5.0f * 3.0f));
	BgImageSet[1].set(
		L"ϣ��֮��",
		Settings::GlobalFont,
		characterSize,
		Settings::NotSeleted,
		sf::Vector2f(Settings::Width / 5.0f * 3.0f, Settings::Height / 5.0f * 3.0f));
	BgImageSet[2].set(
		L"�����ǿ�",
		Settings::GlobalFont,
		characterSize,
		Settings::NotSeleted,
		sf::Vector2f(Settings::Width / 5.0f * 4.0f, Settings::Height / 5.0f * 3.0f));


	MusicOpenSet.set(L"����",
		Settings::GlobalFont,
		characterSize,
		Settings::NotSeleted,
		sf::Vector2f(Settings::Width / 5.0f * 2.0f, Settings::Height / 5.0f * 4.0f));
	MusicTurnSet.set(L"��һ��",
		Settings::GlobalFont,
		characterSize,
		Settings::NotSeleted,
		sf::Vector2f(Settings::Width / 5.0f * 3.0f, Settings::Height / 5.0f * 4.0f));

	returnBox.updateBox(Settings::filesImages[12], 1 / 6.0f);
	returnBox.setPosition(Settings::Width / 15.0f + 20, Settings::Width / 15.0f);

}
//�����¼�ʱ�ж�ѡ��۽�״̬�Լ��Ƿ�
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
			std::cout << "���һ��" << std::endl;
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
				MusicOpenSet.getText().setString(L"����");
			}
			else {
				GlobalGame::bgMusic.stop(); MusicOpenSet.getText().setString(L"�ر�");
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
/*ÿһ�θ��¶������ж����Ȼָ�Ĭ����ʽ��Ȼ�󽫱�ѡ��İ�ť��ɫ��������۽�������»���
ͨ���ñ��������±�ѡ������˴��룬ģʽ����ͳһ*/
void OptionsUI::updateUI(sf::Time delta)
{
	//��ѡ����ʽ�ָ�Ĭ��
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

