#include "Player.h"
#include "./Settings.h"
Things::Things(sf::Vector2f position, int flag, int score) :Things_score(score)
{
	//设置物品的大小
	thingShape.setRadius(Settings::Width / 64.0f);
	resetOrgin(thingShape);
	//记录一下可能的错误Texture引用问题
	thingShape.setTexture(&AssetManager::GetTexture("Image/Things/thing" + std::to_string(flag) + ".png"));
	thingShape.setPosition(position);
}

void Things::renderThings(sf::RenderWindow& window)
{
	window.draw(thingShape);
}
const int Player::InitialSize = 3;
//Player类实体化
Player::Player() :
	isHited(false),
	speedup(false),
	direction(sf::Vector2f(0, -1)),
	nodeRadius(Settings::Width / 100.0f),
	tailOverlap(0u),
	//下面设置长度为1.5个半径是为了在曲角转弯时更加润滑连续
	nodePlayer(sf::Vector2f(nodeRadius* std::sqrt(3)+5, nodeRadius * 1.5)),
	Player_score(InitialSize)
{
	path = std::make_shared<std::deque<sf::Vector2f>>();
	thing_path = std::make_shared<std::deque<sf::Vector2f>>();

	initNodes();
	EFsize[1] = 15;
	EFsize[0] = 30;
	neImageFile[0] = "Image/Effects/粒子_";
	neImageFile[1] = "Image/Effects/龙_";

	//set 皮肤以及相关参数
	NodeFace();

	//pickupBuffer.loadFromFile();
	for (int i = 0; i < pickSoundIndex; i++) {
		pickupSound[i].setBuffer(AssetManager::GetSoundBuffer(Settings::filesSounds[i + 8]));
		pickupSound[i].setVolume(30);
	}

	DragonGo.setBuffer(AssetManager::GetSoundBuffer(Settings::filesSounds[4]));
	DragonGo.setVolume(50);

	overBuffer.loadFromFile(Settings::filesSounds[1]);
	overSound.setBuffer(overBuffer);
	overSound.setVolume(100);

}

void Player::NodeFace() {

	//设置身体参数
	nodeTexture = AssetManager::GetTexture(Settings::filesImages[Settings::FImage + 2]);
	nodeTexture.setSmooth(true);
	nodePlayer.setTexture(&nodeTexture);
	resetOrgin(nodePlayer);

	headTexture = AssetManager::GetTexture(Settings::filesImages[Settings::FImage]);
	headTexture.setSmooth(true);
	sf::Vector2u TextureSize = headTexture.getSize();
	float headScale = nodeRadius / TextureSize.y * 4.5;
	headSprite.setTexture(headTexture); resetOrgin(headSprite);
	headSprite.setScale(headScale, headScale);


}

void Player::processEvent(sf::RenderWindow& window)
{
	if (
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		direction = sf::Vector2f(0, -1);
	else if (
		sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		direction = sf::Vector2f(0, 1);
	else if (
		sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		direction = sf::Vector2f(-1, 0);
	else if (
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		direction = sf::Vector2f(1, 0);

	static double directionSize;
	if (!GlobalGame::mouse.lock && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		static sf::Vector2i MousePosition;
		MousePosition = sf::Mouse::getPosition(window);
		if (
			dis(MousePosition,
				sf::Vector2f(
					Settings::Width / 15.0f * 14.0f,
					Settings::Height / 15.0f)) >
			Settings::Width / 16.0f)
		{
			direction = sf::Vector2f(MousePosition) - toWindow(path->front());
			directionSize = length(direction);
			direction.x /= directionSize;
			direction.y /= directionSize;
		}

	}

		
	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (DragonGo.getStatus() == sf::SoundSource::Status::Stopped) {
			DragonGo.play();
		}
		speedup = true;
	}

	else
		speedup = false;

}


void Player::updatePlayer(sf::Time delta)
{
	move();
	if (++UpdateCDtimes >= 40)
	{
		checkIsOut();
		UpdateCDtimes -= 40;
	}
	checkHit();

}



void Player::getThings(std::deque<Things>& thing_path)
{
	auto toRemove = thing_path.end();
	sf::Vector2f headnode = path->front();
	sf::Vector2f inWinHead(headnode);
	for (auto i = thing_path.begin(); i != thing_path.end(); ++i)
	{
		if (dis(
			(i->thingShape).getPosition(), toWindow(headnode)) <
			nodeRadius + i->thingShape.getRadius())
			toRemove = i;
	}

	if (toRemove != thing_path.end())
	{
		static std::default_random_engine Engine(time(NULL));
		static std::uniform_int_distribution<int> SIndex(0, 20);
		int tem = SIndex(Engine);
		pickupSound[tem % pickSoundIndex].play();
		grow(toRemove->Things_score);
		thing_path.erase(toRemove);
	}
}

bool Player::hitSelf()
{
	return isHited;
}



unsigned Player::getScore()
{
	return Player_score;
}


void Player::initNodes()
{
	path->push_back(sf::Vector2f(
		Settings::Width / 2.0f,
		Settings::Height / 2.0f));
	for (int i = 1; i <= 10 * InitialSize; i++)
	{
		path->push_back(sf::Vector2f(
			Settings::Width / 2.0f -
			direction.x * i * nodeRadius / 5.0,
			Settings::Height / 2.0f -
			direction.y * i * nodeRadius / 5.0));
	}
}

void Player::grow(int score)
{
	tailOverlap += score * 10;
	Player_score += score;
}

void Player::move()
{
	sf::Vector2f& headNode = path->front();
	int times = speedup ? 2 : 1;
	for (int i = 1; i <= times; i++)
	{
		path->push_front(sf::Vector2f(
			headNode.x + direction.x * i * nodeRadius / 5.0,
			headNode.y + direction.y * i * nodeRadius / 5.0));
		if (tailOverlap)
			tailOverlap--;
		else
			path->pop_back();
	}
}

void Player::checkIsOut()
{
	auto isinWindow = [](sf::Vector2f& node) -> bool
	{
		return node.x >= 0 &&
			node.x <= Settings::Width &&
			node.y >= 0 &&
			node.y <= Settings::Height;
	};
	bool OutOfWindow = true;
	//这里可能要更改，对每个节点进行实时更新
	for (auto i : *path)
	{
		if (isinWindow(i))
			OutOfWindow = false;
	}
	if (OutOfWindow)
	{
		sf::Vector2f& tail = path->back();
		if (tail.x < 0)
			for (auto& i : *path)
				i.x = i.x + Settings::Width;
		else if (tail.x > Settings::Width)
			for (auto& i : *path)
				i.x = i.x - Settings::Width;
		else if (tail.y < 0)
			for (auto& i : *path)
				i.y = i.y + Settings::Height;
		else if (tail.y > Settings::Height)
			for (auto& i : *path)
				i.y = i.y - Settings::Height;
	}
}

void Player::checkHit()
{
	sf::Vector2f head = toWindow(path->front());
	int count = 0;
	for (auto i = path->begin()+5; i != path->end(); i++, count++)
		if (count >= 30 && dis(head, toWindow(*i)) < 2.0f * nodeRadius)
		{
			overSound.play();
			sf::sleep(sf::seconds(overBuffer.getDuration().asSeconds()));
			isHited = true;
			break;
		}
}

sf::Vector2f Player::toWindow(sf::Vector2f node)
{
	while (node.x < 0)
		node.x = node.x + Settings::Width;
	while (node.x > Settings::Width)
		node.x = node.x - Settings::Width;
	while (node.y < 0)
		node.y = node.y + Settings::Height;
	while (node.y > Settings::Height)
		node.y = node.y - Settings::Height;
	return node;
}

void Player::renderPlayer(sf::RenderWindow& window)
{
	static int count;
	static sf::Vector2f lastSnakeNode, lastMiddleNode, nowSnakeNode;
	static float angle;
	static sf::Vector2f recDirection;
	static sf::Vector2f NowHeadNode;
	static sf::Vector2f sd1;
	lastSnakeNode = *(path->begin());
	NowHeadNode = toWindow(lastSnakeNode);
	headSprite.setPosition(NowHeadNode);
	recDirection = direction;
	angle =
		std::acos(recDirection.y / length(recDirection)) /
		Settings::pi * 180.0;
	if (direction.x > 0)
		angle = -angle;
	headSprite.setRotation(angle);
	sd1 = sf::Vector2f(5, 5);
	renderNode(NowHeadNode, headSprite, window, 3);

	static long long timer = 0;
	static long long change = 0;
	count = 1;
	/*路径节点间隔为2，半径为10，每隔一个半径进行一次判定
	当半径判定为偶数时，也就是在逻辑圆心绘制关节节点，两个逻辑圆切点为身节点圆心*/
	for (auto i = path->begin() + 5; i != path->end(); i++, count++)
	{
		if (count % 5 == 0)
		{
			if (count % 2)
				lastMiddleNode = *i;
			else
			{
				nowSnakeNode = *i;

				recDirection = nowSnakeNode - lastSnakeNode;
				angle =
					std::acos(recDirection.y / length(recDirection)) /
					Settings::pi * 180.0;
				if (recDirection.x > 0)
					angle = -angle;
				nodePlayer.setRotation(angle);

				static sf::Vector2f wNowSnakeNode;
				static sf::Vector2f wMiddleNode;
				wNowSnakeNode = toWindow(nowSnakeNode);
				wMiddleNode = toWindow(lastMiddleNode);
				renderNode(wNowSnakeNode, nodePlayer, window, 0);
				renderNode(wMiddleNode, nodePlayer, window, 0);
				
				if (Player_score > 16 ) {

					static sf::Sprite NEImage, NEImage2;
					/*如果分数达到一定值，就在这里出特效
									*分别为特效精灵填充纹理，设置方向以及大小
									其实可以在初始化时将图片路径全部写到数组里，但是由于文件名太多，不利于维护*/
					std::string s = neImageFile[0] + std::to_string((timer - 1) % EFsize[0]) + ".png";
					//std::cout << s << std::endl;
					NEImage.setTexture(AssetManager::GetTexture(s));
					//上面这里如果使用count的话，因为count%5时才会进入该语句块，故会造成龙每段身子特效差不多都一样，并且只会在吃到龙珠时发生变化（count随身体长度变化）
					sf::FloatRect NEP1 = NEImage.getLocalBounds();
					NEImage.setScale(128.f / NEP1.width, 77.f / NEP1.height);
					resetOrgin(NEImage);
					NEImage2.setTexture(AssetManager::GetTexture
					(neImageFile[0] + std::to_string((timer) % EFsize[0]) + ".png"));
					resetOrgin(NEImage2);
					sf::FloatRect NEP2 = NEImage2.getLocalBounds();
					NEImage2.setScale(128.f / NEP2.width, 78.f / NEP2.height);
					renderNode(wNowSnakeNode, NEImage, window, 0);
					NEImage2.setRotation(angle);
					renderNode(wMiddleNode, NEImage2, window, 0);

				}

				if (Player_score > 32 && (change) && !(count % 40)) {

					static sf::Sprite NEImage, NEImage2;
					/*如果分数达到一定值，就在这里出特效
									*分别为特效精灵填充纹理，设置方向以及大小
									其实可以在初始化时将图片路径全部写到数组里，但是由于文件名太多，不利于维护*/
					std::string s = neImageFile[1] + std::to_string((timer - 1) % EFsize[1] ) + ".png";
					//std::cout << s << std::endl;
					NEImage.setTexture(AssetManager::GetTexture(s));
					//上面这里如果使用count的话，因为count%5时才会进入该语句块，故会造成龙每段身子特效差不多都一样，并且只会在吃到龙珠时发生变化（count随身体长度变化）
					sf::FloatRect NEP1 = NEImage.getLocalBounds();
					NEImage.setScale(128.f / NEP1.width, 77.f / NEP1.height);
					resetOrgin(NEImage);
					//NEImage2.setTexture(AssetManager::GetTexture
					//(neImageFile[1] + std::to_string((timer) % EFsize[1] ) + ".png"));
					//resetOrgin(NEImage2);
					//sf::FloatRect NEP2 = NEImage2.getLocalBounds();
					//NEImage2.setScale(128.f / NEP2.width, 78.f / NEP2.height);
					NEImage.setRotation(angle);
					renderNode(wNowSnakeNode, NEImage, window, 0);
					//renderNode(wMiddleNode, NEImage2, window, 0);
				}
				renderNode(NowHeadNode, headSprite, window, 3);//再次刷新头部，保证覆盖尾部
				lastSnakeNode = nowSnakeNode;
			}
		}
	}change++; timer++;
}

