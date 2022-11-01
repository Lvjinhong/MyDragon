#pragma once
#include <SFML/Graphics.hpp>
class GlobalTitle {
private:
    sf::Texture titleTexture;
    sf::Sprite titleSprite;
    bool rotateDirection;

public:
    GlobalTitle();

    void update(sf::Time delta);
    void render(sf::RenderWindow& window);
};