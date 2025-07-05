#include "GameObj.h"

// 构造函数，需要给出位置和大小，默认为不可见、无旋转
GameObject::GameObject(const sf::Vector2f& pos, const sf::Vector2f& size)
    : position(pos), size(size), isVisible(false), rotation(0.0f){}

void GameObject::setPosition(const sf::Vector2f& pos) {
    position = pos;
}

void GameObject::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
}

void GameObject::move(const sf::Vector2f& offset) {
    position += offset;
}

void GameObject::move(float dx, float dy) {
    position.x += dx;
    position.y += dy;
}

sf::Vector2f GameObject::getPosition() const {
    return position;
}

void GameObject::setSize(const sf::Vector2f& size) {
    this->size = size;
}

void GameObject::setSize(float width, float height) {
    size.x = width;
    size.y = height;
}

sf::Vector2f GameObject::getSize() const {
    return size;
}

void GameObject::setRotation(float angle) {
    rotation = angle;
}

void GameObject::rotate(float angle) {
    rotation += angle;
}
