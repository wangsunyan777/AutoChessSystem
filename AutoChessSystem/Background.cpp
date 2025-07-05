#include "Background.h"
#include <iostream>
using namespace sf;

// 纹理路径常量定义
const std::string START_BG_PATH = "Textures/desert.png";
const std::string SHOP_BG_PATH = "Textures/teashop.png";
const std::string BATTLE_BG_PATH = "Textures/battleground.png";

Background::Background(int typenum)
    : GameObject(Vector2f(0, 0), Vector2f(800,600)), // (800,600) is the resolution of game window
    currentType(typenum){
    switch (typenum) {
    case 1: { texture.loadFromFile(START_BG_PATH); std::cout << "Loading Start Background\n"; break; }
    case 2: { texture.loadFromFile(SHOP_BG_PATH); std::cout << "Loading Shop Background\n"; break; }
    case 3: { texture.loadFromFile(BATTLE_BG_PATH); std::cout << "Loading Battle Background\n"; break; }
    }
    sprite.setTexture(texture);
}


void Background::update(){}

void Background::render(RenderWindow& window) {
    if (!isVisible) return;
    window.draw(sprite);
}

