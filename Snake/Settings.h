#ifndef SETTINGS_H
#define SETTINGS_H
#include "resource.h"
#include "GlobalTitle.h"
class Settings {
public:
	Settings();	
	static std::shared_ptr<Settings>  GetSettings();
	static sf::Time TimePerFrame;

	//视频Mode初始化
	static sf::VideoMode temp_vm;
	static sf::VideoMode GlobalVideoMode;
	static int Width, Height;
	//颜色以及全局组件初始化
	static sf::Font GlobalFont;
	static  std::shared_ptr<GlobalTitle> globalTitle;
	//static const sf::Color BgImageFile[3];//背景图片
	static const sf::Color GridColor[3];
	static const sf::Color NotSeleted;
	static int GridVisibility; //网格是否可见
	
	static int GridColorOptions;
	
	//游戏主体类初始化
	static sf::String BgImageFiles[7];//背景图片
	static int BgIFoptions; //背景图片选项下标
	static sf::Color PlayerColor[4];//head,body
	static sf::String filesImages[13];//head,body
	static sf::String filesSounds[11];//pickup,over
	static sf::String BgMusic[10];//背景音乐
	static sf::String effectFiles[20];
	static int FImage; //为后续实现换皮肤功能做铺垫
	static int FSound;
	static int Sounds;
	static int FinalSound;//这里当后面得分到达一定程度后（出现特效时）置为0，此时播放升级音效
	static const  float pi ;
	// 使用CRT库的wcstombs()函数将wstring转string，平台无关，需设定locale,这种方法可以兼容中文
	//static std::string WString2String(std::wstring& ws);

private:
		static std::shared_ptr<Settings> Instance;
};
#endif