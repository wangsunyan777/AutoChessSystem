#ifndef GAME_H
#define GAME_H

//#include "simpleAI.h"
#include <SFML/Graphics.hpp>
#include "Background.h"
#include "Button.h"
#include "Item.h"
#include "Soldier.h"
#include "Text.h"
using namespace sf;

class Game {
    friend class Soldier;
private:
    RenderWindow window;

	int gold; // Player's gold, used in shop

	int warriorCount; 
	int mageCount; 
    int killerCount;
    int warriorCount2;
    int mageCount2;
    int killerCount2;//number of soldiers to deploy

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
	Background finalBackground;
	Background loseBackground;
    Background infopage;

    Button start2shop;
    Button shop2battle;
    Button battle2shop;
    Button shop2start;
	Button start2info;
	Button info2start;

    Item warriorItem;
    Item mageItem;
	Item killerItem;
    Item warriorUpgrade;
    Item mageUpgrade;
    Item killerUpgrade; 

	TextObj goldText;
	TextObj roundText;

    void handleItemClick(const Vector2i& mousePosInt);
    void updateItems();

    bool isDeployingSoldier;
    bool inBattle;

    Soldier** AllSoldierPtr;
    int currentSoldier; //正在处理的士兵编号
    int turnCount;
    int round;

    void enterNextRound();
    void resetSoldierCount();
    void updateDisc();

    void deployEnemySoldier();
	void deployPlayerSoldier(const Vector2i& mousePos);

    void createPlayerSoldier();

public:
    Game();
    void run();
    void update();
    void runBattle();
    void draw();
	
};

#endif 