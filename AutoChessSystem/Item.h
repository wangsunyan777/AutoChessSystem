#ifndef ITEM_H
#define ITEM_H

#include "Button.h"
#include <memory>

class Item : public Button {
public:
    friend class Game;

	// ʿ������,1= Warrior, 2 = Mage, 3 = Killer, 
    int type;
private:

    int price;

    //��������������Ⱦ
    Text priceText;
    Sprite icon;

public:
    Item(int type, const Vector2f& size, const Vector2f& position);
	void update(int gold,int count);
    void render(RenderWindow& window) override;
};

#endif
