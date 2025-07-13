#include "Text.h"
TextObj::TextObj(const std::string& str,const Vector2i& Pos,unsigned int size):isVisible(false){
    font.loadFromFile("Font/Arial.ttf");
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(sf::Color::Black);
	text.setPosition(static_cast<float>(Pos.x), static_cast<float>(Pos.y));
}

void TextObj::setString(const std::string& str) {
	text.setString(str);
}

void TextObj::setPosition(float x, float y) {
    text.setPosition(x, y);
}

void TextObj::setColor(const sf::Color& color) {
    text.setFillColor(color);
}

void TextObj::render(sf::RenderWindow& window) {
	if (!isVisible) return;
    window.draw(text);
}
