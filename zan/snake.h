#pragma once
class Wall
{
public:
	void initWall();//��ʼ��ǽ��
	void drawWall();//����ǽ��
	enum { ROW = 26, COL = 26 };
	//�����������ö�ά�������������
	void setWall(int x, int y, char c);
	//�����������û�ȡ��ǰλ�õķ���
	char getWall(int x, int y);

private:
	char gameArray[ROW][COL];
};
class Food
{
public:
	Food(Wall& wall);
	void setFood();
	Wall& wall;
	int Foodx;
	int Foody;
};
class snake
{
public:
	enum { UP = 'w', DOWN = 's', LEFT = 'a', RIGHT = 'd' };
	snake(Wall& wall, Food& food);
	class Point
	{
	public:
		int x;
		int y;
		Point* next;
	};
	void delPoint();
	void initSnake();
	void destroyPoint();
	void addPoint(int x, int y);
	bool move(char c);
	int getsleeptime();
	int countList();
	Point* pHead;
	Food& food;
	Wall& wall;
	bool isRool;
};

