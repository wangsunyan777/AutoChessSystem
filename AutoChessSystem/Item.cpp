#include "Item.h"
#include <iostream>
#include "Game.h"
using namespace sf;

//士兵价格
const int WARRIOR_PRICE = 300;
const int MAGE_PRICE = 400;
const int KILLER_PRICE = 500;
const int WARRIOR_UPGRADE_PRICE = 400;
const int MAGE_UPGRADE_PRICE = 500;
const int KILLER_UPGRADE_PRICE = 500;

//士兵贴图路径
const std::string WARRIOR1_PATH = "Textures/warrior_icon1.png";
const std::string MAGE1_PATH = "Textures/mage_icon1.png";
const std::string KILLER1_PATH = "Textures/killer_icon1.png";
const std::string WARRIOR2_PATH = "Textures/warrior_icon2.png";
const std::string MAGE2_PATH = "Textures/mage_icon2.png";
const std::string KILLER2_PATH = "Textures/killer_icon2.png";

Item::Item(int itemtype, const sf::Vector2f& size, const sf::Vector2f& position)
    : Button(size - Vector2f(0,0), position + Vector2f(10, 100), "",20, Color::Green, Color::Red), type(itemtype){
    static Texture iconTexture1;
    static Texture iconTexture2;
    static Texture iconTexture3;
    static Texture iconTexture4;
    static Texture iconTexture5;
    static Texture iconTexture6;

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
        setButtonString("Killer:\n $400\n BUY: \n (Now: 0)");
        iconTexture3.loadFromFile(KILLER1_PATH);
        icon.setTexture(iconTexture3);
        break;

    case 4:
        price = WARRIOR_UPGRADE_PRICE;
		setButtonString("Warrior Upgrade:\n $400\n BUY: \n (Now: 0)");
		iconTexture4.loadFromFile(WARRIOR2_PATH);
		icon.setTexture(iconTexture4);
		break;

	case 5:
		price = MAGE_UPGRADE_PRICE;
		setButtonString("Mage Upgrade:\n $500\n BUY: \n (Now: 0)");
		iconTexture5.loadFromFile(MAGE2_PATH);
		icon.setTexture(iconTexture5);
		break;

    case 6:
		price = KILLER_UPGRADE_PRICE;
		setButtonString("Killer Upgrade:\n $500\n BUY: \n (Now: 0)");
		iconTexture6.loadFromFile(KILLER2_PATH);
		icon.setTexture(iconTexture6);
		break;
    }

    
	icon.setPosition(position.x, position.y);

    // 初始化价格文本
	static sf::Font font;
	font.loadFromFile("Font/Arial.ttf"); 

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
        setButtonString("Warrior:\n $300\n BUY: \n (Now:" + std::to_string(count) + ")");
        Button::update();
		break;
    case 2:
        setButtonString("Mage:\n $400\n BUY: \n (Now:" + std::to_string(count) + ")");
		Button::update();
        break;
    case 3:
        setButtonString("Killer:\n $500\n BUY: \n (Now:" + std::to_string(count) + ")");
        Button::update();
		break;
    case 4:
        setButtonString("Upgrade:\n $400\n BUY: \n (Now:" + std::to_string(count) + ")");
        Button::update();
        std::cout << "warrior upgrade item called\n";
        break;
    case 5:
        setButtonString("Upgrade:\n $500\n BUY: \n (Now:" + std::to_string(count) + ")");
        Button::update();
        std::cout << "mage upgrade item called\n";
        break;
    case 6:
        setButtonString("Upgrade:\n $500\n BUY: \n (Now:" + std::to_string(count) + ")");
        Button::update();
        std::cout << "killer upgrade item called\n";
        break;
    }
}
