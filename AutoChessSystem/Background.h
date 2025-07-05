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
	int currentType; // 1,2,3�ֱ��Ӧ��ʼ�˵����̵ꡢս������
    Sprite sprite;
    Texture texture;
public:
	// ���캯����typenum��Ӧ��������
    Background(int typenum=1);

    // ʵ�ֻ��ി�麯��
    void render(RenderWindow& window);
    void update();
};

#endif 
