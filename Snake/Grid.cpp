#include "Grid.h"

Grid::Grid()
{
	gridVline.setSize(sf::Vector2f(Settings::Width / 500.0f, Settings::Height));
	gridHline.setSize( sf::Vector2f(Settings::Width, Settings::Height/ 500.0f));
}
//void Grid::deal(sf::RectangleShape& tar, sf::RenderWindow&window,float gridSpace) {
//    for (float i = 0.f; i < Settings::Width; i += gridSpace)
//    {
//        tar.setPosition(i, 0);
//        window.draw(tar);
//    }
//}
void Grid::render(sf::RenderWindow& window)
{
    gridVline.setFillColor(Settings::GridColor[Settings::GridColorOptions]);
    gridHline.setFillColor(Settings::GridColor[Settings::GridColorOptions]);
    //得到网格线间隔，并绘图
    static float gridSpace = Settings::Width / 50.0f;
    for (float i = 0.f; i < Settings::Width; i += gridSpace)
    {
        gridVline.setPosition(i, 0);
        window.draw(gridVline);
    }

    for (float i = 0.f; i < Settings::Height; i += gridSpace)
    {
        gridHline.setPosition(0, i);
        window.draw(gridHline);
    }
}
