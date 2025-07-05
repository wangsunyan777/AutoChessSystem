#include "Game.h"
#include <iostream>
#include "Soldier.h"
#include <cstdlib> //for rand()
#include <Windows.h> //for sleep()
using namespace sf;

const int warriorPrice = 300;
const int magePrice = 500;
const int killerPrice = 500;
const int warrior_upgradePrice = 400;
const int mage_upgradePrice = 500;
const int killer_upgradePrice = 500;

Game::Game():startBackground(1),shopBackground(2),battleBackground(3),
start2shop(Vector2f(400, 100), Vector2f(200, 400), "Shop",Color::White, Color::Red),
shop2battle(Vector2f(200, 100), Vector2f(600, 500), "Battle",Color::Yellow, Color::Red),
battle2shop(Vector2f(200, 50), Vector2f(300, 250), "Shop",Color::Yellow, Color::Red),
shop2start(Vector2f(200, 100), Vector2f(0, 500), "Menu",Color::Yellow, Color::Red),
warriorItem(1, Vector2f(100, 100), Vector2f(0, 1)),
mageItem(2, Vector2f(100, 100), Vector2f(120, 1)),
killerItem(3, Vector2f(100, 100), Vector2f(240, 1)),
isDeployingSoldier(false),inBattle(false),currentSoldier(0),
turnCount(0){

    EnemyWarriorCount = 3;
    EnemyMageCount = 0;
    EnemyKillerCount = 1;

    gold = 1000;
	warriorCount = 0;
	mageCount = 0;
	killerCount = 0;


    //初始化游戏窗口和帧率（SFML）
    window.create(VideoMode(800, 600), "Auto Battler System");
    window.setFramerateLimit(60);

    //初始化士兵AI
    if (!Soldier::initializeAI("./Models/model4.pt")) {
        std::cerr << "Failed to initialize AI model!" << std::endl;
    }
    Soldier::setAIDevice("cpu");

    //进入初始界面
    Game::initStartUI();
    isDeployingSoldier = false;
    inBattle = false;
}

void Game::initStartUI() {
    start2shop.isVisible = true; start2shop.isEnabled = true;
    shop2start.isVisible = false; shop2start.isEnabled = false;
	shop2battle.isVisible = false; shop2battle.isEnabled = false;
	battle2shop.isVisible = false; battle2shop.isEnabled = false;

    startBackground.isVisible = true;
	shopBackground.isVisible = false;
	battleBackground.isVisible = false;

    warriorItem.isVisible = false; warriorItem.isEnabled = false;
    mageItem.isVisible = false; mageItem.isEnabled = false;
    killerItem.isVisible = false; killerItem.isEnabled = false;
}

void Game::initShopUI() {
    start2shop.isVisible = false; start2shop.isEnabled = false;
    shop2start.isVisible = true; shop2battle.isVisible = true;
    shop2start.isEnabled = true; shop2battle.isEnabled = true;
	battle2shop.isVisible = false; battle2shop.isEnabled = false;

    shopBackground.isVisible = true;
    startBackground.isVisible = false;
    battleBackground.isVisible = false;

    warriorItem.isVisible = true; warriorItem.isEnabled = true;
    mageItem.isVisible = true; mageItem.isEnabled = true;
    killerItem.isVisible = true; killerItem.isEnabled = true;
}

void Game::initBattleUI() {
    shop2battle.isVisible = false; shop2battle.isEnabled = false;
    battle2shop.isVisible = false; battle2shop.isEnabled = false;
	shop2start.isVisible = false; shop2start.isEnabled = false;
	start2shop.isVisible = false; start2shop.isEnabled = false;

    battleBackground.isVisible = true;
    shopBackground.isVisible = false;
    startBackground.isVisible = false;

    warriorItem.isVisible = false; warriorItem.isEnabled = false;
    mageItem.isVisible = false; mageItem.isEnabled = false;
    killerItem.isVisible = false; mageItem.isEnabled = false;
}



void Game::run() {
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {


            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed) {
                if (inBattle) continue;
                if (event.mouseButton.button == Mouse::Left && !isDeployingSoldier) {
                    
					if (start2shop.buttonClicked(Mouse::getPosition(window))) {
                        Game::initShopUI();
					}
                    if (shop2start.buttonClicked(Mouse::getPosition(window))) {
                        Game::initStartUI();
                    }
					if (shop2battle.buttonClicked(Mouse::getPosition(window))) {
                        Game::initBattleUI();

                        //设定战斗时士兵位置
                        AllSoldierPtr = new Soldier*[warriorCount + mageCount + killerCount
                            + EnemyWarriorCount + EnemyMageCount + EnemyKillerCount];
                        isDeployingSoldier = true;
						currentSoldier = 0; 
                        //生成对应士兵，并显示在屏幕上方
						for (int i = 0; i < warriorCount; i++) {
							AllSoldierPtr[i] = new Soldier(true, 1, Vector2f(80*i, 0));
						}
                        for (int i = warriorCount; i < warriorCount + mageCount; i++) {
                            AllSoldierPtr[i] = new Soldier(true, 2, Vector2f(80*i, 0));
                        }
						for (int i = warriorCount + mageCount; i < warriorCount + mageCount + killerCount; i++) {
                            AllSoldierPtr[i] = new Soldier(true, 3, Vector2f(80 * i, 0));
						}
                        continue;
					}
                    if (battle2shop.buttonClicked(Mouse::getPosition(window))) {
                        Game::initShopUI();

                    }
                    
                    //Handle items in the shop
                    
					if (warriorItem.buttonClicked(Mouse::getPosition(window))) {
						warriorCount++;
						gold -= warriorPrice; 
						std::cout << "Warrior bought! Current count: " << warriorCount << "\n";
						std::cout << "Remaining gold: " << gold << "\n";
                        warriorItem.Item::update(gold,warriorCount);
						mageItem.Item::update(gold,mageCount);
						killerItem.Item::update(gold,killerCount);
					}
					
					if (mageItem.buttonClicked(Mouse::getPosition(window))) {
						mageCount++;
						gold -= magePrice; 
						std::cout << "Mage bought! Current count: " << mageCount << "\n";
                        std::cout << "Remaining gold: " << gold << "\n";
                        warriorItem.update(gold, warriorCount);
                        mageItem.update(gold, mageCount);
                        killerItem.update(gold, killerCount);
					}

					if (killerItem.buttonClicked(Mouse::getPosition(window))) {
						killerCount++;
						gold -= killerPrice; 
						std::cout << "Killer bought! Current count: " << killerCount << "\n";
                        std::cout << "Remaining gold: " << gold << "\n";
                        warriorItem.update(gold, warriorCount);
                        mageItem.update(gold, mageCount);
                        killerItem.update(gold, killerCount);
					}
                }
                if (event.mouseButton.button == Mouse::Left && isDeployingSoldier) {
                    Vector2i MosPos = Mouse::getPosition(window);
					// Check if the mouse position is within the grid bounds
                    if (MosPos.x < 400 || MosPos.x > 800 || MosPos.y < 120 || MosPos.y > 600) {
                        std::cout << "Mouse position out of bounds!\n";
                        continue;
                    }
                    if (warriorCount > currentSoldier) {
						AllSoldierPtr[currentSoldier]->setPosition(Vector2i(MosPos.x, MosPos.y));
						std::cout << "Warrior deployed at (" << MosPos.x << ", " << MosPos.y << ")\n";
						std::cout << "Current soldier count: " << currentSoldier << "\n";
                        currentSoldier++;
                    }
                    else if (warriorCount+mageCount > currentSoldier) {
                        AllSoldierPtr[currentSoldier]->setPosition(Vector2i(MosPos.x, MosPos.y));
						std::cout << "Mage deployed at (" << MosPos.x << ", " << MosPos.y << ")\n";
                        std::cout << "Current soldier count: " << currentSoldier << "\n";
                        currentSoldier++;
                    }
					else if (killerCount+mageCount+warriorCount > currentSoldier) {
                        AllSoldierPtr[currentSoldier]->setPosition(Vector2i(MosPos.x, MosPos.y));
						std::cout << "Killer deployed at (" << MosPos.x << ", " << MosPos.y << ")\n";
                        std::cout << "Current soldier count: " << currentSoldier << "\n";
                        currentSoldier++;
					}
					if (warriorCount + mageCount + killerCount <= currentSoldier) {
                        draw();
                        Sleep(500);
						isDeployingSoldier = false;
                        inBattle = true;
						std::cout << "All soldiers deployed!\n";
                        Game::deployEnemySoldier();
                        draw();
                        Sleep(500);
                        Game::runBattle();
                        
					}
                }
            }

            if (event.type == Event::MouseButtonReleased) {
                if (event.mouseButton.button == Mouse::Left) {
                    
                }
            }
        }
        draw();
    }
}

void Game::deployEnemySoldier() {
	std::cout << "Deploying enemy soldiers...\n";
    for (int i = warriorCount + mageCount + killerCount; i < warriorCount + mageCount + killerCount + EnemyWarriorCount; i++) {
		AllSoldierPtr[i] = new Soldier(false, 1, Vector2f(80 * i, 0));
    }
    for (int i = warriorCount + mageCount + killerCount + EnemyWarriorCount; i < warriorCount + mageCount + killerCount + EnemyWarriorCount + EnemyMageCount; i++) {
		AllSoldierPtr[i] = new Soldier(false, 2, Vector2f(80 * i, 0));
    }
    for (int i = warriorCount + mageCount + killerCount + EnemyWarriorCount + EnemyMageCount; i < warriorCount + mageCount + killerCount + EnemyWarriorCount + EnemyMageCount + EnemyKillerCount; i++) {
		AllSoldierPtr[i] = new Soldier(false, 3, Vector2f(80 * i, 0));
    }
	// Initialize enemy soldiers with random positions
    int i = warriorCount + mageCount + killerCount;
	while (i < warriorCount + mageCount + killerCount + EnemyWarriorCount + EnemyMageCount + EnemyKillerCount) {
		int x = rand() % 5 + 1; // Random x position
		int y = rand() % 6 + 1; // Random y position

        bool unique=true; //avoid same positions
		for (int j = 0; j < i; j++) {
			if (AllSoldierPtr[j]->x == x && AllSoldierPtr[j]->y == y) {
				unique = false;
				break;
			}
		}
        if (unique) {
            AllSoldierPtr[i]->setPosition(Vector2i(x * 80-80, y * 80 + 40)); // Adjust for the top bar
            i++;
		}
	}
}

void Game::update() {
    
}


void Game::runBattle() {
	// This function will handle the battle logic, which is not implemented yet.
	// It will involve AI for both player and enemy soldiers, and the battle outcome.
	std::cout << "Battle Starts! \n";
    int soldierNum = warriorCount + mageCount + killerCount + EnemyWarriorCount + EnemyMageCount + EnemyKillerCount;
    while (true) {
        bool playerWin = true;
        bool enemyWin = true;

        for (int i = 0; i < soldierNum; i++) {
            if (AllSoldierPtr[i]->isAlive) {
                if (AllSoldierPtr[i]->side == true) enemyWin = false;
                else playerWin = false;
            }
        }
        if (enemyWin) {
            std::cout << "Enemy Wins!\n";
            break;
        }
        if (playerWin) {
            std::cout << "Player Wins!\n";
            break;
        }
        turnCount++;
        for (int i = 0; i < soldierNum; i++) {
            if (AllSoldierPtr[i]->isAlive) {
                std::cout << "calling " << i << " BattleAI" << std::endl;
                AllSoldierPtr[i]->battleAI(AllSoldierPtr, soldierNum, i, turnCount);
                draw(); 
                Sleep(200);
            }
        }
    }
}



void Game::draw() {
    window.clear();

	//let all buttons and backgrounds render one by one. 
    startBackground.render(window);
    shopBackground.render(window);
	battleBackground.render(window);
    start2shop.render(window);
    shop2start.render(window);
    shop2battle.render(window);
    battle2shop.render(window);
    warriorItem.render(window);
    mageItem.render(window);
    killerItem.render(window);

    if (!inBattle) {
        for (int i = 0; i < warriorCount + mageCount + killerCount; i++) {
            if (AllSoldierPtr == nullptr) break;
            if (AllSoldierPtr[i] == nullptr) break;
            if (AllSoldierPtr[i]->isAlive) { AllSoldierPtr[i]->render(window); }
        }
    }
    else {
        for (int i = 0; i < warriorCount + mageCount + killerCount + EnemyWarriorCount + EnemyMageCount + EnemyKillerCount; i++) {
            if (AllSoldierPtr == nullptr) break;
            if (AllSoldierPtr[i] == nullptr) break;
            if (AllSoldierPtr[i]->isAlive) { AllSoldierPtr[i]->render(window); }
        }
    }
    window.display();
}