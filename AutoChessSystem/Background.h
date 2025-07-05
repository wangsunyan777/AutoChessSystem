#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "GameObj.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
using namespace sf;

class Background : public GameObject {
    friend class Button;
    friend class Game;
private:
	int currentType; // 1,2,3分别对应初始菜单、商店、战斗场景
    Sprite sprite;
    Texture texture;
public:
	// 构造函数，typenum对应背景类型
    Background(int typenum=1);

    // 实现基类纯虚函数
    void render(RenderWindow& window);
    void update();
};

#endif 
