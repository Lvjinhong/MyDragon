#pragma once
#include "resource.h"
#include "GlobalGame.h"
class Things {
public:
	sf::CircleShape thingShape;
	int Things_score;

	Things(sf::Vector2f position, int flag, int score);

	void renderThings(sf::RenderWindow& window);
};
class Player {
public:
	Player();

	void processEvent(sf::RenderWindow& window);
	void updatePlayer(sf::Time delta);
	void renderPlayer(sf::RenderWindow& window);

	void getThings(std::deque<Things>& fruits);

	bool hitSelf();

	unsigned getScore();

private:
	void initNodes();
	void grow(int score);//�ɳ����Ե�ʳ����·�����
	void move();//�ƶ�
	void NodeFace();//Ƥ����ʼ��

	void checkIsOut();//����Ƿ������
	void checkHit();

	template <typename T>
	void renderNode(sf::Vector2f& nowPosition, T& shape, sf::RenderWindow& window, int offset);//��Ⱦ���
	

	sf::Vector2f toWindow(sf::Vector2f node);//����ع鴰����
	bool isHited;
	bool speedup;

	sf::Vector2f direction;
	float nodeRadius;
	std::shared_ptr<std::deque<sf::Vector2f> > path;
	std::shared_ptr<std::deque<sf::Vector2f> > thing_path;
	unsigned tailOverlap;


	sf::RectangleShape nodePlayer;
	sf::Texture headTexture;//Ƥ��
	sf::Texture nodeTexture;
	sf::Sprite headSprite;
	int EFsize[2];
	std::string neImageFile[2];

	static const int InitialSize;
	unsigned int Player_score;
	int UpdateCDtimes = 0;

	//sf::SoundBuffer pickupBuffer;
	sf::Sound pickupSound[3];
	int pickSoundIndex = 3;
	sf::SoundBuffer overBuffer;
	sf::Sound overSound;
	 sf::Sound DragonGo;
};

template<typename T>
inline void Player::renderNode(sf::Vector2f& nowPosition, T& shape, sf::RenderWindow& window, int offset)
{
	shape.setPosition(nowPosition);
	window.draw(shape);

	if (nowPosition.x <= nodeRadius + offset)	nowPosition += sf::Vector2f(Settings::Width, 0);
	else if (nowPosition.x >= Settings::Width - nodeRadius - offset)nowPosition-= sf::Vector2f(Settings::Width, 0);
	if (nowPosition.y <= nodeRadius + offset)  nowPosition += sf::Vector2f(0, Settings::Width);
	else if (nowPosition.y >= Settings::Height - nodeRadius - offset)nowPosition-= sf::Vector2f(0, Settings::Width);

	shape.setPosition(nowPosition);
	window.draw(shape);
}
