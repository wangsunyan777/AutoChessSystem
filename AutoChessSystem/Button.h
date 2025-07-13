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
	bool isEnabled; // 按钮是否可用

	// 状态颜色，分为正常状态和禁用状态
    Color normalColor;
    Color disabledColor;
public:
    // 构造函数
    Button(const Vector2f& size = Vector2f(100.0f, 50.0f),
        const Vector2f& position = Vector2f(0.0f, 0.0f),
        const std::string& text = "Null Text",int textSize=20,
        const Color& normalColor = Color::Transparent,
        const Color& disabledColor = Color::Transparent);

    // 实现基类纯虚函数
    void render(RenderWindow& window);
    void update();
    void setButtonString(const std::string& str);
    // 事件处理
    bool buttonClicked(const Vector2i& mousePos);

    // 按钮状态控制
    void setDisabled();
    void setEnabled();
};
#endif
