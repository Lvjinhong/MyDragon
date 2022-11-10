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
	MYSQL mysql;  //mysql����
	MYSQL_RES* res; //һ��������ṹ��   
	MYSQL_ROW row; //char** ��ά���飬���һ������¼  

	const char DataBase_UserName[30] = "lvjinhong";    //���ݿ��û���username
	const char DataBase_Password[30] = "135157";   //���ݿ����룬���Լ�������
	const char DataBase_Host[30] = "43.142.129.117";  //���ݿ����ӵ�ַ
	//ע����ʱ��ʹ������ip�ᱨ����ʱ���Խ�ip��Ϊlocalhost
	const char DataBase_Name[30] = "helloai";  //database name
	unsigned int DataBase_Port = 3306;    //server port


	IMAGE myImage;
	
	float characterSize;
	setBox gotoText[6];//��¼��ע�ᣬ�޸����� ,�˳���¼��������ʷ��¼
	setBox UserText[3];//��δ��ɣ� ��ӭ�㣨�û������û�������ʷ��߷�
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
	bool ConnectDatabase(); //��������
	void FreeConnect();   //�ͷ���Դ
	void logIn();//��¼
	void logIn_Lixian();
	void signUp();//ע����
	void signup_Lixian();
	void modify();
	void modify_Lixian();
	void update_Lixian();

	char* U2G(const char* utf8);
	string G2U(string gbkStr);


};
