#ifndef GameObj_H
#define GameObj_H
#include <SFML/Graphics.hpp>
using namespace sf;

// This is the base class for all game objects in the Auto Battler System.

class GameObject {
protected:
    Vector2f position;    // λ��
    Vector2f size;        // ��С

    float rotation;       // ��ת

public:   
    bool isVisible;       // �ɼ���
	// ���캯������������λ�úʹ�С
    GameObject(const sf::Vector2f& pos = sf::Vector2f(0, 0),
        const sf::Vector2f& size = sf::Vector2f(0, 0));

    // �������Ⱦ�趨Ϊ���麯��
    virtual void render(sf::RenderWindow& window) = 0;
    virtual void update() = 0;

    // ����λ�úʹ�С��ʹ�����غ���
    void setPosition(const sf::Vector2f& pos);
    void setPosition(float x, float y);
    void move(const sf::Vector2f& offset);
    void move(float dx, float dy);
    Vector2f getPosition() const;

    void setSize(const sf::Vector2f& size);
    void setSize(float width, float height);
    Vector2f getSize() const;

    // ��ת����
    void setRotation(float angle);
    void rotate(float angle);

    // ����������
    virtual ~GameObject() = default;
};

#endif