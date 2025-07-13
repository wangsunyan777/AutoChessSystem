#include "Game.h"
#include <iostream>
#include <cstdlib> //for rand()
#include <Windows.h> //for sleep()
using namespace sf;

const int warriorPrice = 300;
const int magePrice = 400;
const int killerPrice = 400;
const int warrior_upgradePrice = 400;
const int mage_upgradePrice = 500;
const int killer_upgradePrice = 500;

//每个关卡敌人的数量
int EnemyWarriors[10] = {2,2,3,3,4,4,4,4,4,4};
int EnemyMages[10] = {0,0,0,0,1,1,1,2,2,2};
int EnemyKillers[10] = {0,0,1,1,1,1,1,1,2,2};

sf::View view(sf::FloatRect(0, 0, 800, 600));

Game::Game() :startBackground(1), shopBackground(2), battleBackground(3), 
finalBackground(4), infopage(5), loseBackground(6),
start2shop(Vector2f(400, 100), Vector2f(200, 300), "Shop",40,Color::White, Color::Red),
shop2battle(Vector2f(200, 100), Vector2f(600, 500), "Battle",40,Color::Yellow, Color::Red),
battle2shop(Vector2f(200, 50), Vector2f(300, 250), "Continue",40,Color::Yellow, Color::Red),
shop2start(Vector2f(200, 100), Vector2f(0, 500), "Menu",40,Color::Yellow, Color::Red),
start2info(Vector2f(400, 100),Vector2f(200, 450),"Info",40,Color::Green, Color::Red),
info2start(Vector2f(300, 100), Vector2f(600, 500),"Back",40, Color::Green, Color::Red),
warriorItem(1, Vector2f(100, 100), Vector2f(0, 1)),
mageItem(2, Vector2f(100, 100), Vector2f(120, 1)),
killerItem(3, Vector2f(100, 100), Vector2f(240, 1)),
warriorUpgrade(4, Vector2f(100, 100), Vector2f(0, 300)),
mageUpgrade(5, Vector2f(100, 100), Vector2f(120, 300)),
killerUpgrade(6, Vector2f(100, 100), Vector2f(240, 300)),
isDeployingSoldier(false),inBattle(false),currentSoldier(0),
turnCount(0),round(0),
goldText("gold: ",Vector2i(400,100), 40), roundText("round: ",Vector2i(100,50), 40) {

    EnemyWarriorCount = EnemyWarriors[round];
    EnemyMageCount = EnemyMages[round];
    EnemyKillerCount = EnemyKillers[round];

    gold = 1000;
	warriorCount = 0;
	mageCount = 0;
	killerCount = 0;
    warriorCount2 = 0;
    mageCount2 = 0;
    killerCount2 = 0;


    //初始化游戏窗口和帧率（SFML）
    window.create(VideoMode(800, 600), "Auto Battler System", sf::Style::Default);
    window.setFramerateLimit(60);
    view = sf::View(sf::FloatRect(0, 0, 800, 600));
    window.setView(view);

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
	start2info.isVisible = true; start2info.isEnabled = true;
	info2start.isVisible = false; info2start.isEnabled = false;

    startBackground.isVisible = true;
	shopBackground.isVisible = false;
	battleBackground.isVisible = false;
    finalBackground.isVisible = false;
    infopage.isVisible = false;

    warriorItem.isVisible = false; warriorItem.Button::isEnabled = false;
    mageItem.isVisible = false; mageItem.isEnabled = false;
    killerItem.isVisible = false; killerItem.isEnabled = false;
	warriorUpgrade.isVisible = false; warriorUpgrade.isEnabled = false;
	mageUpgrade.isVisible = false; mageUpgrade.isEnabled = false;
	killerUpgrade.isVisible = false; killerUpgrade.isEnabled = false;

	goldText.isVisible = false;
	roundText.isVisible = false;
}

void Game::initShopUI() {
    start2shop.isVisible = false; start2shop.isEnabled = false;
    shop2start.isVisible = true; shop2battle.isVisible = true;
    shop2start.isEnabled = true; shop2battle.isEnabled = true;
	battle2shop.isVisible = false; battle2shop.isEnabled = false;
    start2info.isVisible = false; start2info.isEnabled = false;
    info2start.isVisible = false; info2start.isEnabled = false;

    shopBackground.isVisible = true;
    startBackground.isVisible = false;
    battleBackground.isVisible = false;
    finalBackground.isVisible = false;
    infopage.isVisible = false;

    warriorItem.isVisible = true; warriorItem.isEnabled = true;
    mageItem.isVisible = true; mageItem.isEnabled = true;
    killerItem.isVisible = true; killerItem.isEnabled = true;
    warriorUpgrade.isVisible = true; warriorUpgrade.isEnabled = true;
    mageUpgrade.isVisible = true; mageUpgrade.isEnabled = true;
    killerUpgrade.isVisible = true; killerUpgrade.isEnabled = true;

	goldText.isVisible = true;
	roundText.isVisible = false;

	updateItems();//goldText的更新也在这里进行
}

void Game::initBattleUI() {
    shop2battle.isVisible = false; shop2battle.isEnabled = false;
    battle2shop.isVisible = false; battle2shop.isEnabled = false;
	shop2start.isVisible = false; shop2start.isEnabled = false;
	start2shop.isVisible = false; start2shop.isEnabled = false;
	start2info.isVisible = false; start2info.isEnabled = false;
	info2start.isVisible = false; info2start.isEnabled = false;

    battleBackground.isVisible = true;
    shopBackground.isVisible = false;
    startBackground.isVisible = false;
    finalBackground.isVisible = false;
    infopage.isVisible = false;

    warriorItem.isVisible = false; warriorItem.isEnabled = false;
    mageItem.isVisible = false; mageItem.isEnabled = false;
    killerItem.isVisible = false; mageItem.isEnabled = false;
    warriorUpgrade.isVisible = false; warriorUpgrade.isEnabled = false;
    mageUpgrade.isVisible = false; mageUpgrade.isEnabled = false;
    killerUpgrade.isVisible = false; killerUpgrade.isEnabled = false;

	goldText.isVisible = false;
}

void Game::handleItemClick(const Vector2i& mousePosInt) {
    if (warriorItem.buttonClicked(mousePosInt)) {
        warriorCount++;
        gold -= warriorPrice;
        updateItems();
    }

    if (mageItem.buttonClicked(mousePosInt)) {
        mageCount++;
        gold -= magePrice;
        updateItems();
    }

    if (killerItem.buttonClicked(mousePosInt)) {
        killerCount++;
        gold -= killerPrice;
        updateItems();
    }

	if (warriorUpgrade.buttonClicked(mousePosInt)) {
        if (warriorCount >=1) {
			warriorCount2++;
            warriorCount--;
			gold -= warrior_upgradePrice;
            updateItems();
		}
	}
	if (mageUpgrade.buttonClicked(mousePosInt)) {
        if (mageCount >=1 ) {
			mageCount2++;
            mageCount--;
			gold -= mage_upgradePrice;
            updateItems();
		}
	}
	if (killerUpgrade.buttonClicked(mousePosInt)) {
		if (killerCount>=1) {
			killerCount2++;
            killerCount--;
			gold -= killer_upgradePrice;
            updateItems();
		}
	}
}

void Game::createPlayerSoldier() {
    AllSoldierPtr = new Soldier * [warriorCount + mageCount + killerCount
        + warriorCount2 + mageCount2 + killerCount2 + EnemyWarriorCount + EnemyMageCount + EnemyKillerCount];
    for (int i = 0; i < warriorCount; i++) {
        AllSoldierPtr[i] = new Soldier(true, 1, Vector2f(80 * i, 0));
    }
    for (int i = warriorCount; i < warriorCount + mageCount; i++) {
        AllSoldierPtr[i] = new Soldier(true, 2, Vector2f(80 * i, 0));
    }
    for (int i = warriorCount + mageCount; i < warriorCount + mageCount + killerCount; i++) {
        AllSoldierPtr[i] = new Soldier(true, 3, Vector2f(80 * i, 0));
    }
    for (int i = warriorCount + mageCount + killerCount; i < warriorCount + mageCount + killerCount + warriorCount2; i++) {
        AllSoldierPtr[i] = new Soldier(true, 4, Vector2f(80 * i, 0));
    }
    for (int i = warriorCount + mageCount + killerCount + warriorCount2;
        i < warriorCount + mageCount + killerCount + warriorCount2 + mageCount2; i++) {
        AllSoldierPtr[i] = new Soldier(true, 5, Vector2f(80 * i, 0));
    }
    for (int i = warriorCount + mageCount + killerCount + warriorCount2 + mageCount2;
        i < warriorCount + mageCount + killerCount + warriorCount2 + mageCount2 + killerCount2; i++) {
        AllSoldierPtr[i] = new Soldier(true, 6, Vector2f(80 * i, 0));
    }
}


void Game::run() {
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {


            if (event.type == Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, 800, 600);
                view = sf::View(visibleArea);
                window.setView(view);
            }

            if (event.type == Event::MouseButtonPressed) {
                if (inBattle) continue;
                Vector2i windowMousePos = Mouse::getPosition(window);
                Vector2f worldMousePos = window.mapPixelToCoords(windowMousePos);
                Vector2i mousePosInt(static_cast<int>(worldMousePos.x), static_cast<int>(worldMousePos.y));
                if (event.mouseButton.button == Mouse::Left && !isDeployingSoldier) {
					if (info2start.buttonClicked(mousePosInt)) {
                        initStartUI();
					}

					if (start2info.buttonClicked(mousePosInt)) {
						start2info.isVisible = false; start2info.isEnabled = false;
						info2start.isVisible = true; info2start.isEnabled = true;
						infopage.isVisible = true; startBackground.isVisible = false;
						start2shop.isVisible = false; start2shop.isEnabled = false;
					}
					if (start2shop.buttonClicked(mousePosInt)) {
                        Game::initShopUI();
					}
                    if (shop2start.buttonClicked(mousePosInt)) {
                        Game::initStartUI();
                    }
					if (shop2battle.buttonClicked(mousePosInt)) {
                        Game::initBattleUI();
                        isDeployingSoldier = true;
						currentSoldier = 0; 
                        //生成对应士兵，并显示在屏幕上方
						createPlayerSoldier();
                        roundText.isVisible = true;
                        updateDisc();
                        continue;
					}
                    if (battle2shop.buttonClicked(mousePosInt)) {
                        enterNextRound();//关卡胜利，再次进入商店
                        continue;
                    }
                    //Handle click on items in the shop
                    handleItemClick(mousePosInt);
                }

                //战场界面部署士兵
                if (event.mouseButton.button == Mouse::Left && isDeployingSoldier) {
					deployPlayerSoldier(mousePosInt);
                }
            }
        }
        draw();
    }
}

void Game::updateDisc() {
    if (currentSoldier < warriorCount) {
        roundText.setString("Press to Deploy Warrior");
    }
    else if (currentSoldier < warriorCount + mageCount) {
        roundText.setString("Press to Deploy Mage");
    }
    else if (currentSoldier < warriorCount + mageCount + killerCount) {
        roundText.setString("Press to Deploy Killer");
    }
    else if (currentSoldier < warriorCount + mageCount + killerCount + warriorCount2) {
        roundText.setString("Press to Deploy Warrior Upgrade");
    }
    else if (currentSoldier < warriorCount + mageCount + killerCount + warriorCount2 + mageCount2) {
        roundText.setString("Press to Deploy Mage Upgrade");
    }
    else if (currentSoldier < warriorCount + mageCount + killerCount + warriorCount2 + mageCount2 + killerCount2) {
        roundText.setString("Press to Deploy Killer Upgrade");
    }
}

void Game::deployPlayerSoldier(const Vector2i& MosPos) {
    if (MosPos.x < 400 || MosPos.x > 800 || MosPos.y < 120 || MosPos.y > 600) {
        std::cout << "Mouse position out of bounds!\n";
    }
    else if (warriorCount > currentSoldier) {
        AllSoldierPtr[currentSoldier]->setPosition(Vector2i(MosPos.x, MosPos.y));
        std::cout << "Warrior deployed at (" << MosPos.x << ", " << MosPos.y << ")\n";
        std::cout << "Current soldier count: " << currentSoldier << "\n";
        currentSoldier++;
        updateDisc();
    }
    else if (warriorCount + mageCount > currentSoldier) {
        AllSoldierPtr[currentSoldier]->setPosition(Vector2i(MosPos.x, MosPos.y));
        std::cout << "Mage deployed at (" << MosPos.x << ", " << MosPos.y << ")\n";
        std::cout << "Current soldier count: " << currentSoldier << "\n";
        currentSoldier++;
        updateDisc();
    }
    else if (killerCount + mageCount + warriorCount > currentSoldier) {
        AllSoldierPtr[currentSoldier]->setPosition(Vector2i(MosPos.x, MosPos.y));
        std::cout << "Killer deployed at (" << MosPos.x << ", " << MosPos.y << ")\n";
        std::cout << "Current soldier count: " << currentSoldier << "\n";
        currentSoldier++;
        updateDisc();
    }
	else if (warriorCount + mageCount + killerCount + warriorCount2 > currentSoldier) {
		AllSoldierPtr[currentSoldier]->setPosition(Vector2i(MosPos.x, MosPos.y));
		std::cout << "Warrior Upgrade deployed at (" << MosPos.x << ", " << MosPos.y << ")\n";
		std::cout << "Current soldier count: " << currentSoldier << "\n";
		currentSoldier++;
        updateDisc();
	}
	else if (warriorCount + mageCount + killerCount + warriorCount2 + mageCount2 > currentSoldier) {
		AllSoldierPtr[currentSoldier]->setPosition(Vector2i(MosPos.x, MosPos.y));
		std::cout << "Mage Upgrade deployed at (" << MosPos.x << ", " << MosPos.y << ")\n";
		std::cout << "Current soldier count: " << currentSoldier << "\n";
		currentSoldier++;
        updateDisc();
	}
	else if (warriorCount + mageCount + killerCount + warriorCount2 + mageCount2 + killerCount2 > currentSoldier) {
		AllSoldierPtr[currentSoldier]->setPosition(Vector2i(MosPos.x, MosPos.y));
		std::cout << "Killer Upgrade deployed at (" << MosPos.x << ", " << MosPos.y << ")\n";
		std::cout << "Current soldier count: " << currentSoldier << "\n";
		currentSoldier++;
        updateDisc();
	}
    if (warriorCount + mageCount + killerCount+ warriorCount2 + mageCount2 + killerCount2 <= currentSoldier) {
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

void Game::deployEnemySoldier() {
	std::cout << "Deploying enemy soldiers...\n";
    roundText.setString("Enemy is deploying! ");
	int playerSoldier = warriorCount + mageCount + killerCount + warriorCount2 + mageCount2 + killerCount2;
    for (int i = playerSoldier; i < playerSoldier + EnemyWarriorCount; i++) {
		AllSoldierPtr[i] = new Soldier(false, 1, Vector2f(80 * i, 0));
        currentSoldier++;
    }
    for (int i = playerSoldier + EnemyWarriorCount; i < playerSoldier + EnemyWarriorCount + EnemyMageCount; i++) {
		AllSoldierPtr[i] = new Soldier(false, 2, Vector2f(80 * i, 0));
        currentSoldier++;
    }
    for (int i = playerSoldier + EnemyWarriorCount + EnemyMageCount; i < playerSoldier + EnemyWarriorCount + EnemyMageCount + EnemyKillerCount; i++) {
		AllSoldierPtr[i] = new Soldier(false, 3, Vector2f(80 * i, 0));
        currentSoldier++;
    }
	// Initialize enemy soldiers with random positions
    int i = playerSoldier;
	while (i < playerSoldier + EnemyWarriorCount + EnemyMageCount + EnemyKillerCount) {
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
            AllSoldierPtr[i]->setPosition(Vector2i(x * 80-80, y * 80 + 40));
			AllSoldierPtr[i]->render(window);
            i++;
            Sleep(200);
		}
	}
}

void Game::update() {
    
}


void Game::runBattle() {
	// This function will handle the battle logic, which is not implemented yet.
	// It will involve AI for both player and enemy soldiers, and the battle outcome.
	std::cout << "Battle Starts! \n";
    roundText.isVisible = true;
    roundText.setString("Round: " + std::to_string(round + 1) + "/10");
    int soldierNum = warriorCount + mageCount + killerCount +
        warriorCount2 + mageCount2 + killerCount2 +
        EnemyWarriorCount + EnemyMageCount + EnemyKillerCount;
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
			battleBackground.isVisible = false;
			loseBackground.isVisible = true;
            break;
        }
        if (playerWin) {
            std::cout << "Player Wins!\n";
			battle2shop.isVisible = true;
			battle2shop.isEnabled = true;
            inBattle = false;
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
    finalBackground.render(window);
    infopage.render(window);

	start2info.render(window);
	info2start.render(window);
    start2shop.render(window);
    shop2start.render(window);
    shop2battle.render(window);
    battle2shop.render(window);

    warriorItem.render(window);
    mageItem.render(window);
    killerItem.render(window);
    warriorUpgrade.render(window);
	mageUpgrade.render(window);
	killerUpgrade.render(window);
	goldText.render(window);
	roundText.render(window);

    if (!inBattle) {
		int playerSoldiers = warriorCount + mageCount + killerCount +
			warriorCount2 + mageCount2 + killerCount2;
        for (int i = 0; i < currentSoldier; i++) {
            if (AllSoldierPtr == nullptr) break;
            else if (AllSoldierPtr[i] == nullptr) break;
            else if (AllSoldierPtr[i]->isAlive) { AllSoldierPtr[i]->render(window); }
        }
    }
    else {
		int totalSoldiers = warriorCount + mageCount + killerCount +
			warriorCount2 + mageCount2 + killerCount2 +
			EnemyWarriorCount + EnemyMageCount + EnemyKillerCount;
        for (int i = 0; i < currentSoldier; i++) {
            if (AllSoldierPtr == nullptr) break;
            else if (AllSoldierPtr[i] == nullptr) break;
            else if (AllSoldierPtr[i]->isAlive) { AllSoldierPtr[i]->render(window); }
        }
    }
    loseBackground.render(window);

    window.display();
}

void Game::resetSoldierCount() {
	int playerSoldierCount = warriorCount + mageCount + killerCount;
	warriorCount = 0;
	mageCount = 0;
	killerCount = 0;

	currentSoldier = 0;

	if (AllSoldierPtr != nullptr) {
		for (int i = 0; i < playerSoldierCount; i++) {
            if (AllSoldierPtr[i]->isAlive == false) {
				delete AllSoldierPtr[i];
                continue;
            }
            switch(AllSoldierPtr[i]->type){
			case 1: warriorCount++; delete AllSoldierPtr[i]; break;
			case 2: mageCount++; delete AllSoldierPtr[i]; break;
			case 3: killerCount++; delete AllSoldierPtr[i]; break;
			case 4: warriorCount2++; delete AllSoldierPtr[i]; break;
			case 5: mageCount2++; delete AllSoldierPtr[i]; break;
			case 6: killerCount2++; delete AllSoldierPtr[i]; break;
			default: std::cout << "Error: Unknown soldier type!\n"; break;
			}
		}
		delete[] AllSoldierPtr;
		AllSoldierPtr = nullptr;
	}
}


void Game::enterNextRound() {
	std::cout << "Entering next round...\n";
    round++;
	if (round >= 10) {
		std::cout << "Game Over! You have completed all rounds!\n";
		finalBackground.isVisible = true;
		startBackground.isVisible = false;
		shopBackground.isVisible = false;
		battleBackground.isVisible = false;
		infopage.isVisible = false;
		battle2shop.isVisible = false;
		roundText.isVisible = false;
		for (int i = 0; i < warriorCount + mageCount + killerCount + warriorCount2 + mageCount2 + killerCount2 + EnemyWarriorCount + EnemyMageCount + EnemyKillerCount; i++) {
            AllSoldierPtr[i]->isAlive = false;
		}
		return;
	}
	EnemyWarriorCount = EnemyWarriors[round];
	EnemyMageCount = EnemyMages[round];
	EnemyKillerCount = EnemyKillers[round];
    gold += 500;
	gold += 50 * (round - 1);
    Game::resetSoldierCount();
	std::cout << "current gold: " << gold << "\n";
	std::cout << "current warrior: " << warriorCount << "\n";
	std::cout << "current mage: " << mageCount << "\n";
	std::cout << "current killer: " << killerCount << "\n";
	std::cout << "current warrior2: " << warriorCount2 << "\n";
	std::cout << "current mage2: " << mageCount2 << "\n";
	std::cout << "current killer2: " << killerCount2 << "\n";
    std::cout << "current round: " << round << "\n";
    Game::initShopUI();
	turnCount = 0; 
	isDeployingSoldier = false;
    inBattle = false;
	currentSoldier = 0; 
	EnemyWarriorCount = EnemyWarriors[round];
	EnemyMageCount = EnemyMages[round];
	EnemyKillerCount = EnemyKillers[round];
}

void Game::updateItems() {
    warriorItem.isEnabled = true; mageItem.isEnabled = true;
    killerItem.isEnabled = true; warriorUpgrade.isEnabled = true;
	mageUpgrade.isEnabled = true; killerUpgrade.isEnabled = true;
    if (gold < warriorPrice) {
        warriorItem.isEnabled = false;
    }
	if (gold < magePrice) {
		mageItem.isEnabled = false;
	}
	if (gold < killerPrice) {
		killerItem.isEnabled = false;
	}
	if (warriorCount < 1 || gold < warrior_upgradePrice) {
		warriorUpgrade.isEnabled = false;
	}
	if (mageCount < 1 || gold < mage_upgradePrice) {
		mageUpgrade.isEnabled = false;
	}
	if (killerCount < 1 || gold < killer_upgradePrice) {
		killerUpgrade.isEnabled = false;
	}
	goldText.setString("Gold: " + std::to_string(gold));
	warriorItem.update(gold, warriorCount);
	mageItem.update(gold, mageCount);
	killerItem.update(gold, killerCount);
	warriorUpgrade.update(gold, warriorCount2);
	mageUpgrade.update(gold, mageCount2);
	killerUpgrade.update(gold, killerCount2);
}