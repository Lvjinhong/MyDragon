#pragma once
#include "resource.h"
#include "Grid.h"
#include "./GlobalGame.h"
class Box {
public:
	Box();

	void updateBox(sf::String file, float scale = 1 / 4.0f);

	void setPosition(sf::Vector2f& pos);
	void setPosition(float x, float y);

	void setFocus(bool status);
	//bool getFocus();
	void renderBox(sf::RenderWindow& window);
	sf::Sprite& getBoxSprite();
	bool contain(float x, float y);
	bool contain(sf::Vector2f point);
	//按钮变化的颜色，0位是默认颜色
	const sf::Color colors[2];



private:
	sf::Texture Box_texture;
	sf::Sprite Box_sprite;
	bool Box_focused;
};




//setBox是一个字体类，通过对文字样式的修改呈现出界面设置选项
class setBox {
private:
	sf::Text setBoxText;
	sf::Color setBoxColor;
	sf::Color selectedColor = sf::Color::Yellow;
public:
	void set(
		sf::String content,
		sf::Font& font,
		float characterSize,
		sf::Color color,
		sf::Vector2f position);
	void clear();//恢复默认样式
	void focused();//处于聚焦状态，出现下划线
	void seleted();//被选择后变色
	sf::Text& getText();
	void render(sf::RenderWindow& window);//刷新字体

	template <typename T>
	bool contains(sf::Vector2<T> point);//检测选项是否被聚焦，即计算鼠标位置是否被包含
};
template <typename T>
bool setBox::contains(sf::Vector2<T> point)
{
	return setBoxText.getGlobalBounds().contains(static_cast<sf::Vector2f>(point));
}
