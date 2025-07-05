#ifndef GameObj_H
#define GameObj_H
#include <SFML/Graphics.hpp>
using namespace sf;

// This is the base class for all game objects in the Auto Battler System.

class GameObject {
protected:
    Vector2f position;    // 位置
    Vector2f size;        // 大小

    float rotation;       // 旋转

public:   
    bool isVisible;       // 可见性
	// 构造函数，可以设置位置和大小
    GameObject(const sf::Vector2f& pos = sf::Vector2f(0, 0),
        const sf::Vector2f& size = sf::Vector2f(0, 0));

    // 对象的渲染设定为纯虚函数
    virtual void render(sf::RenderWindow& window) = 0;
    virtual void update() = 0;

    // 设置位置和大小，使用重载函数
    void setPosition(const sf::Vector2f& pos);
    void setPosition(float x, float y);
    void move(const sf::Vector2f& offset);
    void move(float dx, float dy);
    Vector2f getPosition() const;

    void setSize(const sf::Vector2f& size);
    void setSize(float width, float height);
    Vector2f getSize() const;

    // 旋转控制
    void setRotation(float angle);
    void rotate(float angle);

    // 虚析构函数
    virtual ~GameObject() = default;
};

#endif