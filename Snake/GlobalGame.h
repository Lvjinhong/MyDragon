#ifndef GLOBALGAME
#define GLOBALGAME
#include "./resource.h"
#include "UI.h"
class Check {
public:
	sf::Clock clock;
	sf::Time cd;
	bool lock;
	Check();
	void work();
};
class GlobalGame
{
public:

	GlobalGame();
	void play();
	void ProcessEvent();
	void update(sf::Time delta);
	void render();
	

	static Check mouse;
	static Check keyboard;

	static std::shared_ptr<UI> MainUIptr;
	static std::shared_ptr<UI> UserUIptr;
	static std::shared_ptr<UI> TmpUIptr;
	static std::shared_ptr<UI> TmpGameUIptr;
	//全局属性设置
	static std::string MyUsername ;
	static sf::String MyPassword;
	static int HistoryScore;
	static bool isLogin;
	

	static sf::Music bgMusic;
private:
	sf::RenderWindow window;
	
	
};

template<typename T>
inline sf::FloatRect resetOrgin(T& model)
{
	{
		sf::FloatRect Borders = model.getLocalBounds();
		model.setOrigin(Borders.left + Borders.width / 2,
			Borders.top + Borders.height / 2);//看看是不是这个问题
		return Borders;
	}
}

template<typename T1, typename T2>
float dis(sf::Vector2<T1> node1, sf::Vector2<T2> node2)
{
	return std::sqrt(
		std::pow(
			(
				static_cast<double>(node1.x) -
				static_cast<double>(node2.x)),
			2) +
		std::pow(
			(
				static_cast<double>(node1.y) -
				static_cast<double>(node2.y)),
			2));
}

template<typename T>
float length(sf::Vector2<T> node)
{
	return std::sqrt(
		std::pow(static_cast<double>(node.x), 2) +
		std::pow(static_cast<double>(node.y), 2));
}

#endif

