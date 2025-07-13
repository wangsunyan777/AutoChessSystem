#ifndef BUTTON_H

#define BUTTON_H
#include <SFML/Graphics.hpp>

#include "GameObj.h"
#include <functional>

using namespace sf;

class Button : public GameObject {
	friend class Game;
	friend class Background; 
protected:
    RectangleShape shape;
    Text txt;
	bool isEnabled; // ��ť�Ƿ����

	// ״̬��ɫ����Ϊ����״̬�ͽ���״̬
    Color normalColor;
    Color disabledColor;
public:
    // ���캯��
    Button(const Vector2f& size = Vector2f(100.0f, 50.0f),
        const Vector2f& position = Vector2f(0.0f, 0.0f),
        const std::string& text = "Null Text",int textSize=20,
        const Color& normalColor = Color::Transparent,
        const Color& disabledColor = Color::Transparent);

    // ʵ�ֻ��ി�麯��
    void render(RenderWindow& window);
    void update();
    void setButtonString(const std::string& str);
    // �¼�����
    bool buttonClicked(const Vector2i& mousePos);

    // ��ť״̬����
    void setDisabled();
    void setEnabled();
};
#endif
