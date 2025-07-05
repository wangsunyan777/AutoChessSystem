#include "Button.h"
#include <iostream>
using namespace sf;
Button::Button(const Vector2f& size, 
    const Vector2f& position,
    const std::string& text, 
    const Color& normal_color,
    const Color& disabled_color): 
	GameObject(position, size), 
    normalColor(normal_color), 
    disabledColor(disabled_color),
	isEnabled(false)
 {

    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(normalColor); 


    // font必须设为静态变量，确保字体不会被销毁，从而渲染时不会引发错误，这个BUG改了一上午:(
	static sf::Font font; 

    if (!font.loadFromFile("Arial.ttf")) {
        std::cout << "字体加载失败！" << std::endl;
    }

    txt.setFont(font);
    txt.setString(text);
    txt.setCharacterSize(20);
	txt.setFillColor(Color::Black);

    FloatRect textRect = txt.getGlobalBounds();
    txt.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    txt.setPosition(Button::position.x + Button::size.x / 2.0f, Button::position.y + Button::size.y / 2.0f);

	//this->isEnabled = false; // 默认按钮不可用
	//this->isVisible = false; // 默认不可见
    
}


void Button::setDisabled() {
	isEnabled = false;
	shape.setFillColor(disabledColor);
}

void Button::setEnabled() {
	isEnabled = true;
	shape.setFillColor(normalColor);
}

void Button::render(RenderWindow& window) {
    if (!this->isVisible) return;
    window.draw(shape);
    window.draw(txt);
}

void Button::update() {
	if (isEnabled) {
		shape.setFillColor(normalColor);
	}
	else {
		shape.setFillColor(disabledColor);
	}
}

bool Button::buttonClicked(const Vector2i& mousePos) {
    if (!isVisible) return false;
    if (!isEnabled) return false;

	// 判断鼠标位置是否在按钮的边界内
    float x1 = shape.getPosition().x;
	float y1 = shape.getPosition().y;
	float x2 = x1 + shape.getSize().x;
	float y2 = y1 + shape.getSize().y;
	bool isClicked = (mousePos.x >= x1 && mousePos.x <= x2 &&
		mousePos.y >= y1 && mousePos.y <= y2);
    if (isClicked) {
        std::cout << "Clicked" << std::endl; return true;
    }
    return false;
}

void Button::setButtonString(const std::string& str) {
	txt.setString(str);
	FloatRect textRect = txt.getGlobalBounds();
	txt.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	txt.setPosition(Button::position.x + Button::size.x / 2.0f, Button::position.y + Button::size.y / 2.0f);
}



