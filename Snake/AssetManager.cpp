#include "AssetManager.h"

std::shared_ptr<AssetManager> AssetManager::Instance =std::make_shared<AssetManager>();
AssetManager::AssetManager()
{
    assert(Instance == nullptr);
    std::cout << "AssetManager初始化完毕" << std::endl;
}

sf::SoundBuffer& AssetManager::GetSoundBuffer(std::string const& filename)
{
    // TODO: 在此处插入 return 语句
    auto& sBufferMap = Instance->SoundBuffers;

    auto pairFound = sBufferMap.find(filename);
    if (pairFound != sBufferMap.end()) {
        return pairFound->second;
    }
    auto& sBuffer = sBufferMap[filename];
    sBuffer.loadFromFile(filename);
    return sBuffer;
}

sf::Font& AssetManager::GetFont(std::string const& filename)
{
    // TODO: 在此处插入 return 语句
    auto& fontMap = Instance->Fonts;

    auto pairFound = fontMap.find(filename);
    if (pairFound != fontMap.end()) {
        return pairFound->second;
    }

    auto& font = fontMap[filename];
    font.loadFromFile(filename);
    return font;
}

sf::Texture& AssetManager::GetTexture(std::string const& filename) {
    auto& texMap = Instance->Textures;

    auto pairFound = texMap.find(filename);
    if (pairFound != texMap.end()) {
        return pairFound->second;
    }

    auto& texture = texMap[filename];
    texture.loadFromFile(filename);
    return texture;
}
