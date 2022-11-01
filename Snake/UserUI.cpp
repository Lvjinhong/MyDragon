#include "UserUI.h"
#include <graphics.h>
#include "GlobalGame.h"
#include "rankUI.h"
UserUI::UserUI() :setFocus(-1)
{
	characterSize = Settings::Width / 25.f;
	gotoText[0].set(
		L"��¼", Settings::GlobalFont,
		characterSize,
		Settings::NotSeleted,
		sf::Vector2f(Settings::Width / 5.0f, Settings::Height / 5.f * 3.0f)
	);

	gotoText[1].set(
		L"ע��", Settings::GlobalFont,
		characterSize,
		Settings::NotSeleted,
		sf::Vector2f(Settings::Width / 5.0f * 2.0f, Settings::Height / 5.f * 3.0f)
	);

	gotoText[2].set(
		L"�޸�����", Settings::GlobalFont,
		characterSize,
		Settings::NotSeleted,
		sf::Vector2f(Settings::Width / 5.0f * 3.0f, Settings::Height / 5.f * 3.0f)
	);

	gotoText[3].set(
		L"�˳���¼", Settings::GlobalFont,
		characterSize,
		Settings::NotSeleted,
		sf::Vector2f(Settings::Width / 5.0f * 3.0f, Settings::Height / 5.f )
	);
	gotoText[4].set(
		L"���¼�¼", Settings::GlobalFont,
		characterSize,
		Settings::NotSeleted,
		sf::Vector2f(Settings::Width / 5.0f * 3.0f, Settings::Height / 5.f*2 )
	);
	gotoText[5].set(
		L"���а�", Settings::GlobalFont,
		characterSize,
		Settings::NotSeleted,
		sf::Vector2f(Settings::Width / 5.f*2, Settings::Height / 5.f * 4)
	);

	returnBox.updateBox(Settings::filesImages[12], 1 / 6.0f);
	returnBox.setPosition(Settings::Width / 15.0f + 20, Settings::Width / 15.0f);

	ConnectDatabase(); //�������ݿ�
	sf::String temp(Settings::BgImageFiles[3]);

	//loadimage(&myImage, temp.toAnsiString().c_str(), Settings::Width, Settings::Height);
}

void UserUI::processEvent(sf::RenderWindow& window)
{
	auto mousePosition = sf::Mouse::getPosition(window);
	setFocus = -1;
	//�ֱ�Ϊ��¼��ע�ᣬ�޸�����
	if (gotoText[0].contains(mousePosition))
	{
		setFocus = 0;
		if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			logIn();
			return;
		}
	}
	if (gotoText[1].contains(mousePosition))
	{
		setFocus = 1;
		if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			UserSound.setBuffer(AssetManager::GetSoundBuffer(Settings::filesSounds[2]));
			UserSound.setVolume(50);
			UserSound.play();
			signUp();
			return;
		}
	}
	if (gotoText[2].contains(mousePosition))
	{
		setFocus = 2;
		if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			modify();
			return;
		}
	}
	//�˳���¼
	if (gotoText[3].contains(mousePosition))
	{
		setFocus = 3;
		if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			GlobalGame::isLogin = false;
			GlobalGame::MyUsername = "Please Login";
			GlobalGame::HistoryScore = 0;
			return;
		}
	}
	//ˢ�¼�¼
	if (gotoText[4].contains(mousePosition)) {
		setFocus = 4;
		if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			update(GlobalGame::HistoryScore);
			return;
		}
	}
	//�������а�
	if (gotoText[5].contains(mousePosition)) {
		setFocus = 5;
		if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			GlobalGame::TmpGameUIptr = GlobalGame::MainUIptr;
			GlobalGame::MainUIptr = std::make_shared<rankUI>();
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

void UserUI::updateUI(sf::Time delta)
{
	//Settings::globalTitle.update(delta);
	for (auto& i : gotoText) {
		i.clear();
	}
	if (setFocus != -1) {
		gotoText[setFocus].focused();
	}
	if (GlobalGame::isLogin)
		//�û���¼״̬
	{
		UserText[1].set(
			L"��ӭ�� : " + sf::String(GlobalGame::MyUsername), Settings::GlobalFont,
			characterSize,
			Settings::NotSeleted,
			sf::Vector2f(Settings::Width / 5.0f+70 , Settings::Height / 5.f+20 )
		);
		UserText[2].set(L"��ʷ��¼:" + sf::String(to_string(GlobalGame::HistoryScore)), Settings::GlobalFont,
			characterSize,
			Settings::NotSeleted,
			sf::Vector2f(Settings::Width / 5.0f+70, Settings::Height / 5.f * 2.0f+20));
	}
	else {
		UserText[1].set(
			GlobalGame::MyUsername, Settings::GlobalFont,
			characterSize,
			Settings::NotSeleted,
			sf::Vector2f(Settings::Width / 5.0f+70 , Settings::Height / 5.f+20) );
		UserText[2].set(L"", Settings::GlobalFont,
			characterSize,
			Settings::NotSeleted,
			sf::Vector2f(Settings::Width / 5.0f+70, Settings::Height / 5.f * 2.0f+20));

	}


}

void UserUI::renderUI(sf::RenderWindow& window)
{
	//Settings::globalTitle.render(window);
	for (auto& i : gotoText) {
		i.render(window);
	}
	for (auto& i : UserText)i.render(window);
	returnBox.renderBox(window);
}



bool UserUI::ConnectDatabase()
{
	//��ʼ��mysql
	mysql_init(&mysql);   //����mysql�����ݿ�
	if (!(mysql_real_connect(&mysql, DataBase_Host, DataBase_UserName, DataBase_Password, DataBase_Name, DataBase_Port, NULL, 0))) //�м�ֱ����������û��������룬���ݿ������˿ںţ�����дĬ��0����3306�ȣ���������д�ɲ����ٴ���ȥ
	{
		printf("Error connecting to database:%s\n", mysql_error(&mysql));
		MessageBoxA(NULL, "���ӷ�����ʧ�ܣ�", "����", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	else
	{
		//MessageBoxA(NULL, "����MYSQL���ݳɹ���", "��Ϣ", MB_OK);
		printf("Connected Successful\n");
		return true;
	}
}

void UserUI::FreeConnect()
{
	//�ͷ���Դ
	//mysql_free_result(res);
	mysql_close(&mysql);
}

void UserUI::logIn()
{
	//initgraph(Settings::Width, Settings::Height);
	initgraph(0, 0);
	//putimage(0, 0, &myImage);

	char pt1[20], pt2[20];

	while (1) {
		InputBox(pt1, 20, "�������û���");
		InputBox(pt2, 20, "����������");
		//wstring tt1 = wstring(pt1), tt2 = wstring(pt2);
		//string InputUsrname = Settings::WString2String(tt1), InputUsrname = Settings::WString2String(tt2);
		string InputUsrname(pt1), InputPassword(pt2);
		int f = 0;
		//ѡ������ݿ��е�һ������������� sheet8 ��һ�����ݱ�
		//mysql_query(&mysql, "set names utf8");
		mysql_query(&mysql, "SELECT * from UserManager");
		//��ȡ�����
		res = mysql_store_result(&mysql);
		while (row = mysql_fetch_row(res))
		{
			//cout << row[0] << " " << row[1] <<" " << row[2] << endl;
			if (InputUsrname == U2G(row[0]) && InputPassword == U2G(row[1])) {
				f = 1;
				MessageBoxA(NULL, "��ӭ����Ϸ���飡", "��¼�ɹ�", MB_OK | MB_ICONINFORMATION);
				GlobalGame::MyUsername = InputUsrname;
				GlobalGame::MyPassword = InputPassword;
				GlobalGame::HistoryScore = atoi(row[2]);
				GlobalGame::isLogin = true;
				break;
			}
		}
		if (!f)
			f = MessageBoxA(NULL, "��¼ʧ�ܣ������û����������Ƿ����", "��ܰ��ʾ", MB_RETRYCANCEL | MB_ICONEXCLAMATION);
		if (f != 4) {
			break;
		}
	}
	closegraph();
}

void UserUI::signUp()
{

	initgraph(0, 0);
	putimage(0, 0, &myImage);

	char t1[20], t2[20];
	char buffer[240] = {};
	while (1) {
		int fl = 0;
		InputBox(t1, 20, "������Ȩ����Կ");
		if (myKey != t1) {
			fl = MessageBoxA(NULL, "��Կ��Դ�����������˧ȡ����ϵ��", "��ܰ��ʾ", MB_RETRYCANCEL | MB_ICONEXCLAMATION);
			if (fl == 4)continue;
			closegraph();
			return;
		}
		break;
	}


	//�ж��û����Ƿ��Ѿ����ڣ����������ʾ��������
	while (1) {
		InputBox(t1, 20, "������ע���û���");
		InputBox(t2, 20, "������ע������");
		int f = 0;
		sf::String temp(t1);
		mysql_query(&mysql, "SELECT * from UserManager");
		//��ȡ�����
		res = mysql_store_result(&mysql);
		while (row = mysql_fetch_row(res)) {
			if (temp == U2G(row[0])) {//�û����Ѿ�����
				f = MessageBoxA(NULL, "�û����Ѵ��ڣ���һ�����԰ȣ�", "��ܰ��ʾ", MB_RETRYCANCEL | MB_ICONEXCLAMATION);
				break;
			}
		}
		if (f == 4)continue;
		else if (f == 2) break;
		//wstring tt1 = wstring(t1), tt2 = wstring(t2);
		//string T1 =Settings::WString2String(tt1), T2=Settings::WString2String(tt1);
		sprintf(buffer, "INSERT INTO UserManager(Username,Password,Score) VALUES('%s','%s','0')", t1, t2);
		mysql_query(&mysql, G2U(buffer).c_str());
		int t = mysql_affected_rows(&mysql);
		//ע��ɹ���ʧ�ܽ����ж�
		if (t != -1) {
			MessageBoxA(NULL, "��ϲ��ע��ɹ���", "��ܰ��ʾ", MB_OK | MB_ICONINFORMATION);
		}
		else {
			f = MessageBoxA(NULL, "ע��ʧ�ܣ����Ժ����� ", "��ܰ��ʾ", MB_RETRYCANCEL | MB_ICONEXCLAMATION);
		}

		if (f != 4)break;
	}

	closegraph();
}

//������ʷ��¼
void UserUI::update(int score)
{
	char buffer[108];
	sprintf(buffer, "UPDATE UserManager SET Score = '%d'  WHERE Username = '%s' ", GlobalGame::HistoryScore, GlobalGame::MyUsername.c_str());
	mysql_query(&mysql, G2U(buffer).c_str());
	int temp = mysql_affected_rows(&mysql);
	if (temp == 1) {
		MessageBoxA(NULL, "��ϲ�����³ɹ���", "��ܰ��ʾ", MB_OK | MB_ICONINFORMATION);
	}
	//cout << temp << endl;

}


void UserUI::modify()
{
	initgraph(0, 0);
	//putimage(0, 0, &myImage);

	char  t2[20];
	char buffer[240] = {};
	if (!GlobalGame::isLogin) {
		MessageBoxA(NULL, "���ȵ�¼", "��ܰ��ʾ", MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	if (GlobalGame::MyUsername == "lvdashuai") {
		MessageBoxA(NULL, "�����˺Ų����޸����룡", "��ܰ��ʾ", MB_OK | MB_ICONEXCLAMATION);
		closegraph();
		return;
	}

	while (1) {

		InputBox(t2, 20, "������������");
		//wstring tt2(t2);
		//string  T2 = Settings::WString2String(tt2);
		int f = 0;
		string s1 = GlobalGame::MyUsername, finnalWords;
		finnalWords = string("UPDATE UserManager SET Password = '") + t2 + string("' WHERE Username = '") + string(s1) + string("' ");
		mysql_query(&mysql, finnalWords.c_str());
		int t = mysql_affected_rows(&mysql);
		//ע��ɹ���ʧ�ܽ����ж�
		if (t == 1) {
			MessageBoxA(NULL, "��ϲ���޸ĳɹ���", "��ܰ��ʾ", MB_OK | MB_ICONINFORMATION);
		}
		else {
			f = MessageBoxA(NULL, "�޸�ʧ�ܣ����Ժ����ԣ�", "��ܰ��ʾ", MB_RETRYCANCEL | MB_ICONEXCLAMATION);
		}
		if (f != 4)break;
	}
	closegraph();
}


/*��װת�뺯�� �ֱ�ΪUTF8ת��GBK���Լ�GBKת��UTF8
��ҪΪ�˽��VS�����ݿ�֮�������ַ���������*/
char* UserUI::U2G(const char* utf8)//UTF8ת��Ϊ GB2312  �����ݿ�õ��Ľ����ʾ��������
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr)
	{
		delete[] wstr;
		wstr = NULL;
	}
	return str;
}
string UserUI::G2U(string gbkStr)
{
	string outUtf8 = "";
	int n = MultiByteToWideChar(CP_ACP, 0, gbkStr.c_str(), -1, NULL, 0);
	WCHAR* str1 = new WCHAR[n];
	MultiByteToWideChar(CP_ACP, 0, gbkStr.c_str(), -1, str1, n);
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
	char* str2 = new char[n];
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
	outUtf8 = str2;
	delete[]str1;
	str1 = NULL;
	delete[]str2;
	str2 = NULL;
	return outUtf8;
}