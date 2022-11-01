#include "./Settings.h"
using namespace std;
std::shared_ptr<Settings> Settings::Instance = std::make_shared<Settings>();

sf::Time Settings::TimePerFrame = sf::seconds(1.f / 100.f);
Settings::Settings()
{
	std::cout << "Settings初始化完毕" << std::endl;
}
sf::VideoMode Settings::temp_vm = sf::VideoMode::getDesktopMode();
sf::VideoMode Settings::GlobalVideoMode = sf::VideoMode(Settings::temp_vm.width / 2, Settings::temp_vm.height / 2, Settings::temp_vm.bitsPerPixel);
int Settings::Width = Settings::temp_vm.width / 2;
int Settings::Height = Settings::temp_vm.height / 2;
std::shared_ptr<Settings> Settings::GetSettings()
{
	return Instance;
}

//std::string Settings::WString2String(std::wstring& ws)
//{	// 使用CRT库的wcstombs()函数将wstring转string，平台无关，需设定locale,这种方法可以兼容中文
//
//		string curLocale = setlocale(LC_ALL, NULL);
//		setlocale(LC_ALL, "chs");
//
//		const wchar_t* _Source = ws.c_str();
//		size_t _Dsize = 2 * ws.size() + 1;
//		char* _Dest = new char[_Dsize];
//		memset(_Dest, 0, _Dsize);
//		wcstombs(_Dest, _Source, _Dsize);
//
//		string result = _Dest;
//		delete[] _Dest;
//
//		setlocale(LC_ALL, curLocale.c_str());
//		return result;
//
//}

//颜色以及按钮初始化
int Settings::GridVisibility = 0;
int Settings::GridColorOptions = 0;
int Settings::BgIFoptions = 0;

sf::Font Settings::GlobalFont = sf::Font();
  std::shared_ptr<GlobalTitle> Settings::globalTitle=nullptr;
/*背景图片
0-2:3张背景图
3：登录窗口Bg图
4:logo
5:关于界面
*/
sf::String Settings::BgImageFiles[7] = {"Image\\BgImage\\BgI1.png",
"Image\\BgImage\\BgI2.png" ,
"Image\\BgImage\\BgI3.png" ,
"Image\\BgImage\\BgI4.png","Image\\BgImage\\GlobalTitle.png","Image\\BgImage\\AboutText.png"};

const sf::Color Settings::GridColor[] =
{
	sf::Color(0xecefeb70), // 飞雪
	sf::Color(0x4ab43470), // 苍木
	sf::Color(0xeef42f70) //鎏金
};
const sf::Color Settings::NotSeleted =
sf::Color::White;

//游戏主体类初始化

sf::Color Settings::PlayerColor[4] = { sf::Color(0xf1c40fff),sf::Color(0x1c2833ff)};//原来的身体颜色变化

/*
head*2,body*2,分别是龙头与龙身体的皮肤，后续可以增加皮肤修改功能
5:设置按钮图片
6:返回游戏按钮图片
7:退出按钮图片
8:暂停按钮图片
9:开始按钮图片
10:前往我的 按钮
11:前往关于 按钮
12:返回按钮
*/																					
sf::String Settings::filesImages[13] = {"","Image/head.png","Image/head2.png","Image/body.png",
"Image/body2.png","Image/setUI.png","Image/returnUI.png",
"Image/exitUI.png","Image/pauseUI.png","Image/startUI.png","Image/UserUI.png","Image/AboutUI.png","Image/returnRealUI.png"};

/*

1 结束游戏音效
2 注册时获取权限提示音
3 跳转到关于页面提示音
4 空格加速时龙吟声


8 拿到物品音效1
9 拿到物品音效2
10 拿到物品音效3
*/
sf::String  Settings::filesSounds[11] = {"Music/pickup.wav","Music/die.wav",
"Music/getLv.wav","Music/Myway.wav","Music/DrangonGo.wav"," "," "," ","Music/pickup1.wav",
"Music/pickup2.wav","Music/pickup3.wav"};
//背景音乐
sf::String Settings::BgMusic[10] = { "Music/BgM1.wav","Music/BgM2.wav","Music/BgM3.wav","Music/BgM4.wav",
"Music/BgM5.wav","Music/BgM6.wav"," "};
//int Settings::PColor[2] = {0,1};//body圆节点,方形连接节点,设置这个是为了 选项里可以更换皮肤
int Settings::FImage = 1;//后面可以换皮肤
//后面通过FSound%Sounds+5 实现音乐轮播
int Settings::Sounds= 7;
int Settings::FSound= 0;

int Settings::FinalSound = -1;

const  float Settings::pi = 3.141592653;