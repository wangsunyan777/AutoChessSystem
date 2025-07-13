#pragma once
#include "GameObj.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <SFML/Window.hpp>
using namespace sf;
class TextObj {
public:
    TextObj(const std::string& str, const Vector2i& Pos,unsigned int size);

    void setString(const std::string& str);
    void setPosition(float x, float y);
    void setColor(const sf::Color& color);
    void render(sf::RenderWindow& window);

    bool isVisible;

private:
    sf::Text text;
    sf::Font font;
};
#pragma once
