#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H
#include "resource.h"
class AssetManager
{
public:

	static sf::SoundBuffer& GetSoundBuffer(std::string const& filename);
	static sf::Font& GetFont(std::string const& filename);
	static sf::Texture& GetTexture(std::string const& filename);
	AssetManager();
private:
	
	std::map<std::string, sf::Texture> Textures;
	std::map<std::string, sf::SoundBuffer> SoundBuffers;
	std::map<std::string, sf::Font> Fonts;
	//单例模式，保证了AssetManager全局唯一，且任意位置访问
	static std::shared_ptr<AssetManager> Instance;
};
#endif