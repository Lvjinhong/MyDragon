#pragma once
#include "UI.h"
#include <graphics.h>
#include <windows.h>
#include "mysql.h"
#include "Box.h"
using namespace std;
class ranks {
public:
	string username;
	int score;
};
class UserUI :public UI {
private:
	MYSQL mysql;  //mysql连接
	MYSQL_RES* res; //一个结果集结构体   
	MYSQL_ROW row; //char** 二维数组，存放一条条记录  

	const char DataBase_UserName[30] = "lvjinhong";    //数据库用户名username
	const char DataBase_Password[30] = "135157";   //数据库密码，填自己的密码
	const char DataBase_Host[30] = "43.142.129.117";  //数据库连接地址
	//注意有时候使用主机ip会报错，此时可以将ip改为localhost
	const char DataBase_Name[30] = "helloai";  //database name
	unsigned int DataBase_Port = 3306;    //server port


	IMAGE myImage;
	
	float characterSize;
	setBox gotoText[6];//登录，注册，修改密码 ,退出登录，更新历史记录
	setBox UserText[3];//暂未完成， 欢迎你（用户），用户名，历史最高分
	int setFocus, UserFocs;
	Box returnBox;
	string myKey = "woaiAI";
	sf::Sound UserSound;
	
public:
	UserUI();

	void processEvent(sf::RenderWindow& window);
	void updateUI(sf::Time delta);
	void renderUI(sf::RenderWindow& window);

	void update(int score);
	bool ConnectDatabase(); //函数申明
	void FreeConnect();   //释放资源
	void logIn();//登录
	void logIn_Lixian();
	void signUp();//注册检测
	void signup_Lixian();
	void modify();
	void modify_Lixian();
	void update_Lixian();

	char* U2G(const char* utf8);
	string G2U(string gbkStr);


};
