#include "Item.h"
#include <iostream>
#include "Game.h"
using namespace sf;

//士兵价格
const int WARRIOR_PRICE = 300;
const int MAGE_PRICE = 400;
const int KILLER_PRICE = 500;

//士兵贴图路径
const std::string WARRIOR1_PATH = "Textures/warrior_icon1.png";
const std::string MAGE1_PATH = "Textures/mage_icon1.png";
const std::string KILLER1_PATH = "Textures/killer_icon1.png";

Item::Item(int itemtype, const sf::Vector2f& size, const sf::Vector2f& position)
    : Button(size - Vector2f(0,0), position + Vector2f(10, 100), "", Color::Green, Color::Red), type(itemtype){
    static Texture iconTexture1;
    static Texture iconTexture2;
    static Texture iconTexture3;

    switch (type) {
    case 1:
        price = WARRIOR_PRICE;
        setButtonString("Warrior:\n $300\n BUY: \n (Now: 0)");
        if (!iconTexture1.loadFromFile(WARRIOR1_PATH)) {
            std::cout << "Load File Failure!\n";
        };
        icon.setTexture(iconTexture1);
        break;

    case 2:
        price = MAGE_PRICE;
        setButtonString("Mage:\n $400\n BUY: \n (Now: 0)");
        iconTexture2.loadFromFile(MAGE1_PATH);
        icon.setTexture(iconTexture2);
        break;

    case 3:
        price = KILLER_PRICE;
        setButtonString("Killer:\n $500\n BUY: \n (Now: 0)");
        iconTexture3.loadFromFile(KILLER1_PATH);
        icon.setTexture(iconTexture3);
        break;
    }
    
	icon.setPosition(position.x, position.y);

    // 初始化价格文本
	static sf::Font font;
	font.loadFromFile("Arial.ttf"); 

    priceText.setFont(font);
    priceText.setString("Price: " + std::to_string(price));
    priceText.setCharacterSize(16);
    priceText.setFillColor(sf::Color::White);
    priceText.setPosition(position.x+10, position.y + size.y+20);


}

void Item::render(RenderWindow& window) {
	if (!isVisible) return; 
    //渲染图标
    window.draw(icon);
    window.draw(priceText);
    

    //渲染按钮
    Button::render(window);
}

void Item::update(int gold,int count){
    switch (type){
    case 1:
		if (gold < WARRIOR_PRICE){
            isEnabled = false;
        }
        setButtonString("Warrior:\n $300\n BUY: \n (Now:" + std::to_string(count) + ")");
        Button::update();
		break;
    case 2:
        if (gold < MAGE_PRICE){ 
            isEnabled = false; 
        }
        setButtonString("Mage:\n $400\n BUY: \n (Now:" + std::to_string(count) + ")");
		Button::update();
        break;
    case 3:
		if (gold < KILLER_PRICE) {
			isEnabled = false;
		}
        setButtonString("Killer:\n $500\n BUY: \n (Now:" + std::to_string(count) + ")");
        Button::update();
		break;
    }
}
