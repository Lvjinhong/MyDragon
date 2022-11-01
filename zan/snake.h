#pragma once
class Wall
{
public:
	void initWall();//初始化墙壁
	void drawWall();//画出墙壁
	enum { ROW = 26, COL = 26 };
	//根据索引设置二维数组里面的内容
	void setWall(int x, int y, char c);
	//根据索引设置获取当前位置的符号
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

