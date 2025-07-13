#include "Background.h"
#include <iostream>
using namespace sf;

// 纹理路径常量定义
const std::string START_BG_PATH = "Textures/desert.png";
const std::string SHOP_BG_PATH = "Textures/shop.png";
const std::string BATTLE_BG_PATH = "Textures/battleground.png";
const std::string FINAL_BG_PATH = "Textures/win.png";
const std::string INFO_BG_PATH = "Textures/info.png";
const std::string LOSE_BG_PATH = "Textures/lose.png";
Background::Background(int typenum)
    : GameObject(Vector2f(0, 0), Vector2f(800,600)), // (800,600) is the resolution of game window
    currentType(typenum){
    switch (typenum) {
    case 1: { texture.loadFromFile(START_BG_PATH);break; }
    case 2: { texture.loadFromFile(SHOP_BG_PATH); break; }
    case 3: { texture.loadFromFile(BATTLE_BG_PATH); break; }
    case 4: {texture.loadFromFile(FINAL_BG_PATH); break;}
	case 5: { texture.loadFromFile(INFO_BG_PATH); break; }
	case 6: { texture.loadFromFile(LOSE_BG_PATH); break; }
    }
    sprite.setTexture(texture);
}


void Background::update(){}

void Background::render(RenderWindow& window) {
    if (!isVisible) return;
    window.draw(sprite);
}

