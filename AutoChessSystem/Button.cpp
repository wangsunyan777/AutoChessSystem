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


    // font������Ϊ��̬������ȷ�����岻�ᱻ���٣��Ӷ���Ⱦʱ���������������BUG����һ����:(
	static sf::Font font; 

    if (!font.loadFromFile("Arial.ttf")) {
        std::cout << "�������ʧ�ܣ�" << std::endl;
    }

    txt.setFont(font);
    txt.setString(text);
    txt.setCharacterSize(20);
	txt.setFillColor(Color::Black);

    FloatRect textRect = txt.getGlobalBounds();
    txt.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    txt.setPosition(Button::position.x + Button::size.x / 2.0f, Button::position.y + Button::size.y / 2.0f);

	//this->isEnabled = false; // Ĭ�ϰ�ť������
	//this->isVisible = false; // Ĭ�ϲ��ɼ�
    
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

	// �ж����λ���Ƿ��ڰ�ť�ı߽���
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



