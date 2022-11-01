#include "Box.h"

Box::Box() :colors{ sf::Color::White ,sf::Color(0x6005fe)}
{
    Box_focused = false;
}

void Box::updateBox(sf::String file, float scale)//更新按钮图标（相当于初始化）
{
	Box_texture= AssetManager::GetTexture(file);
	Box_texture.setSmooth(true);
	Box_sprite.setTexture(Box_texture);
	sf::FloatRect border = resetOrgin(Box_sprite);
	Box_sprite.setScale(Settings::Width / border.width * scale, Settings::Width / border.width * scale);
}
void Box::setPosition(sf::Vector2f& pos)//函数重载
{
    Box_sprite.setPosition(pos.x, pos.y);
}
void Box::setPosition(float x,float y)//设置按钮位置
{
    Box_sprite.setPosition(x, y);
}
void Box::setFocus(bool status)//聚焦时变色 
{
    Box_focused = status;
    Box_focused ? Box_sprite.setColor(colors[1]) : Box_sprite.setColor(colors[0]);
}

//bool Box::getFocus() 
//{
//    return Box_focused;
//}

void Box::renderBox(sf::RenderWindow& window) 
{
    window.draw(Box_sprite);
}

sf::Sprite& Box::getBoxSprite()
{
    return Box_sprite;
    // TODO: 在此处插入 return 语句
}

//setBox实现
void setBox::set(
    sf::String content,
    sf::Font& font,
    float characterSize,
    sf::Color color,
    sf::Vector2f position)
{
    setBoxText.setFont(font);
    setBoxText.setCharacterSize(characterSize);
    setBoxText.setFillColor(color);

    resetOrgin(setBoxText); 
    setBoxText.setPosition(position);

    setBoxText.setString(content);
    setBoxColor = color;
}

void setBox::clear()
{
    setBoxText.setStyle(sf::Text::Regular);
    setBoxText.setFillColor(setBoxColor);
}

void setBox::focused()
{
    setBoxText.setStyle(sf::Text::Underlined);
}

void setBox::seleted()
{
    setBoxText.setFillColor(selectedColor);
}

sf::Text& setBox::getText()
{
    // TODO: 在此处插入 return 语句
    return setBoxText;
}

void setBox::render(sf::RenderWindow& window)
{
    window.draw(setBoxText);
}