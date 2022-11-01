#include "UserUI.h"
#include <graphics.h>
#include "GlobalGame.h"
#include "rankUI.h"
UserUI::UserUI() :setFocus(-1)
{
	characterSize = Settings::Width / 25.f;
	gotoText[0].set(
		L"登录", Settings::GlobalFont,
		characterSize,
		Settings::NotSeleted,
		sf::Vector2f(Settings::Width / 5.0f, Settings::Height / 5.f * 3.0f)
	);

	gotoText[1].set(
		L"注册", Settings::GlobalFont,
		characterSize,
		Settings::NotSeleted,
		sf::Vector2f(Settings::Width / 5.0f * 2.0f, Settings::Height / 5.f * 3.0f)
	);

	gotoText[2].set(
		L"修改密码", Settings::GlobalFont,
		characterSize,
		Settings::NotSeleted,
		sf::Vector2f(Settings::Width / 5.0f * 3.0f, Settings::Height / 5.f * 3.0f)
	);

	gotoText[3].set(
		L"退出登录", Settings::GlobalFont,
		characterSize,
		Settings::NotSeleted,
		sf::Vector2f(Settings::Width / 5.0f * 3.0f, Settings::Height / 5.f )
	);
	gotoText[4].set(
		L"更新记录", Settings::GlobalFont,
		characterSize,
		Settings::NotSeleted,
		sf::Vector2f(Settings::Width / 5.0f * 3.0f, Settings::Height / 5.f*2 )
	);
	gotoText[5].set(
		L"排行榜", Settings::GlobalFont,
		characterSize,
		Settings::NotSeleted,
		sf::Vector2f(Settings::Width / 5.f*2, Settings::Height / 5.f * 4)
	);

	returnBox.updateBox(Settings::filesImages[12], 1 / 6.0f);
	returnBox.setPosition(Settings::Width / 15.0f + 20, Settings::Width / 15.0f);

	ConnectDatabase(); //连接数据库
	sf::String temp(Settings::BgImageFiles[3]);

	//loadimage(&myImage, temp.toAnsiString().c_str(), Settings::Width, Settings::Height);
}

void UserUI::processEvent(sf::RenderWindow& window)
{
	auto mousePosition = sf::Mouse::getPosition(window);
	setFocus = -1;
	//分别为登录，注册，修改密码
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
	//退出登录
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
	//刷新记录
	if (gotoText[4].contains(mousePosition)) {
		setFocus = 4;
		if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			update(GlobalGame::HistoryScore);
			return;
		}
	}
	//进入排行榜
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
		//用户登录状态
	{
		UserText[1].set(
			L"欢迎你 : " + sf::String(GlobalGame::MyUsername), Settings::GlobalFont,
			characterSize,
			Settings::NotSeleted,
			sf::Vector2f(Settings::Width / 5.0f+70 , Settings::Height / 5.f+20 )
		);
		UserText[2].set(L"历史记录:" + sf::String(to_string(GlobalGame::HistoryScore)), Settings::GlobalFont,
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
	//初始化mysql
	mysql_init(&mysql);   //连接mysql，数据库
	if (!(mysql_real_connect(&mysql, DataBase_Host, DataBase_UserName, DataBase_Password, DataBase_Name, DataBase_Port, NULL, 0))) //中间分别是主机，用户名，密码，数据库名，端口号（可以写默认0或者3306等），可以先写成参数再传进去
	{
		printf("Error connecting to database:%s\n", mysql_error(&mysql));
		MessageBoxA(NULL, "连接服务器失败！", "错误", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	else
	{
		//MessageBoxA(NULL, "连接MYSQL数据成功！", "消息", MB_OK);
		printf("Connected Successful\n");
		return true;
	}
}

void UserUI::FreeConnect()
{
	//释放资源
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
		InputBox(pt1, 20, "请输入用户名");
		InputBox(pt2, 20, "请输入密码");
		//wstring tt1 = wstring(pt1), tt2 = wstring(pt2);
		//string InputUsrname = Settings::WString2String(tt1), InputUsrname = Settings::WString2String(tt2);
		string InputUsrname(pt1), InputPassword(pt2);
		int f = 0;
		//选择该数据库中的一个表的所有数据 sheet8 是一个数据表
		//mysql_query(&mysql, "set names utf8");
		mysql_query(&mysql, "SELECT * from UserManager");
		//获取结果集
		res = mysql_store_result(&mysql);
		while (row = mysql_fetch_row(res))
		{
			//cout << row[0] << " " << row[1] <<" " << row[2] << endl;
			if (InputUsrname == U2G(row[0]) && InputPassword == U2G(row[1])) {
				f = 1;
				MessageBoxA(NULL, "欢迎来到戏龙珠！", "登录成功", MB_OK | MB_ICONINFORMATION);
				GlobalGame::MyUsername = InputUsrname;
				GlobalGame::MyPassword = InputPassword;
				GlobalGame::HistoryScore = atoi(row[2]);
				GlobalGame::isLogin = true;
				break;
			}
		}
		if (!f)
			f = MessageBoxA(NULL, "登录失败，请检查用户名或密码是否错误！", "温馨提示", MB_RETRYCANCEL | MB_ICONEXCLAMATION);
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
		InputBox(t1, 20, "请输入权限密钥");
		if (myKey != t1) {
			fl = MessageBoxA(NULL, "密钥配对错误，请与吕大帅取得联系！", "温馨提示", MB_RETRYCANCEL | MB_ICONEXCLAMATION);
			if (fl == 4)continue;
			closegraph();
			return;
		}
		break;
	}


	//判定用户名是否已经存在，如果存在提示重新输入
	while (1) {
		InputBox(t1, 20, "请输入注册用户名");
		InputBox(t2, 20, "请输入注册密码");
		int f = 0;
		sf::String temp(t1);
		mysql_query(&mysql, "SELECT * from UserManager");
		//获取结果集
		res = mysql_store_result(&mysql);
		while (row = mysql_fetch_row(res)) {
			if (temp == U2G(row[0])) {//用户名已经存在
				f = MessageBoxA(NULL, "用户名已存在，换一个试试叭！", "温馨提示", MB_RETRYCANCEL | MB_ICONEXCLAMATION);
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
		//注册成功与失败进行判定
		if (t != -1) {
			MessageBoxA(NULL, "恭喜，注册成功！", "温馨提示", MB_OK | MB_ICONINFORMATION);
		}
		else {
			f = MessageBoxA(NULL, "注册失败，请稍后重试 ", "温馨提示", MB_RETRYCANCEL | MB_ICONEXCLAMATION);
		}

		if (f != 4)break;
	}

	closegraph();
}

//更新历史记录
void UserUI::update(int score)
{
	char buffer[108];
	sprintf(buffer, "UPDATE UserManager SET Score = '%d'  WHERE Username = '%s' ", GlobalGame::HistoryScore, GlobalGame::MyUsername.c_str());
	mysql_query(&mysql, G2U(buffer).c_str());
	int temp = mysql_affected_rows(&mysql);
	if (temp == 1) {
		MessageBoxA(NULL, "恭喜，更新成功！", "温馨提示", MB_OK | MB_ICONINFORMATION);
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
		MessageBoxA(NULL, "请先登录", "温馨提示", MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	if (GlobalGame::MyUsername == "lvdashuai") {
		MessageBoxA(NULL, "试用账号不可修改密码！", "温馨提示", MB_OK | MB_ICONEXCLAMATION);
		closegraph();
		return;
	}

	while (1) {

		InputBox(t2, 20, "请输入新密码");
		//wstring tt2(t2);
		//string  T2 = Settings::WString2String(tt2);
		int f = 0;
		string s1 = GlobalGame::MyUsername, finnalWords;
		finnalWords = string("UPDATE UserManager SET Password = '") + t2 + string("' WHERE Username = '") + string(s1) + string("' ");
		mysql_query(&mysql, finnalWords.c_str());
		int t = mysql_affected_rows(&mysql);
		//注册成功与失败进行判定
		if (t == 1) {
			MessageBoxA(NULL, "恭喜，修改成功！", "温馨提示", MB_OK | MB_ICONINFORMATION);
		}
		else {
			f = MessageBoxA(NULL, "修改失败，请稍后再试！", "温馨提示", MB_RETRYCANCEL | MB_ICONEXCLAMATION);
		}
		if (f != 4)break;
	}
	closegraph();
}


/*封装转码函数 分别为UTF8转到GBK，以及GBK转到UTF8
主要为了解决VS与数据库之间中文字符乱码问题*/
char* UserUI::U2G(const char* utf8)//UTF8转化为 GB2312  从数据库得到的结果显示中文正常
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