#pragma once
#include "resource.h"
class Grid {
 
public:
    Grid();
    void deal(sf::RectangleShape& tar, sf::RenderWindow& window,float gridSpace);
    void render(sf::RenderWindow& window);
private:
    sf::RectangleShape gridVline;  
    sf::RectangleShape gridHline;  
    
};
