#ifndef GAME_H
#define GAME_H

//#include "simpleAI.h"
#include <SFML/Graphics.hpp>
#include "Background.h"
#include "Button.h"
#include "Item.h"
#include "Soldier.h"

using namespace sf;

class Game {
    friend class Soldier;
private:
    RenderWindow window;

	int gold; // Player's gold, used in shop

	int warriorCount; 
	int mageCount; 
    int killerCount; //number of soldiers to deploy

    int EnemyWarriorCount;
    int EnemyMageCount;
    int EnemyKillerCount;

    void initStartUI();
    void initShopUI();
    void initBattleUI();


    //All game objects are elements of Game class
    Background startBackground;
    Background shopBackground;
    Background battleBackground;

    Button start2shop;
    Button shop2battle;
    Button battle2shop;
    Button shop2start;

    Item warriorItem;
    Item mageItem;
	Item killerItem;

    bool isDeployingSoldier;
    bool inBattle;

    Soldier** AllSoldierPtr;
    int currentSoldier; //正在处理的士兵编号
    int turnCount;

public:
    Game();
    void run();
    void update();
    void runBattle();
    void draw();
	void deployEnemySoldier();
};

#endif 