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
	//��ť�仯����ɫ��0λ��Ĭ����ɫ
	const sf::Color colors[2];



private:
	sf::Texture Box_texture;
	sf::Sprite Box_sprite;
	bool Box_focused;
};




//setBox��һ�������࣬ͨ����������ʽ���޸ĳ��ֳ���������ѡ��
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
	void clear();//�ָ�Ĭ����ʽ
	void focused();//���ھ۽�״̬�������»���
	void seleted();//��ѡ����ɫ
	sf::Text& getText();
	void render(sf::RenderWindow& window);//ˢ������

	template <typename T>
	bool contains(sf::Vector2<T> point);//���ѡ���Ƿ񱻾۽������������λ���Ƿ񱻰���
};
template <typename T>
bool setBox::contains(sf::Vector2<T> point)
{
	return setBoxText.getGlobalBounds().contains(static_cast<sf::Vector2f>(point));
}
