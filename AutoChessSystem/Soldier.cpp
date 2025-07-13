#include "Soldier.h"
#include "AI_action_converter.h"
#include <cmath>
#include <iostream>
#include <Windows.h>
AI_model Soldier::ai;
bool Soldier::AI_initialized = false;

Soldier::Soldier(bool whichside, int typenum=1, const Vector2f& position = Vector2f(0,0))
	:side(whichside),type(typenum) {
	x = (int)((position.x) / 80) + 1;
	y = (int)((position.y-120.0) / 80) + 1;

	if (typenum == 1) { //warrior
		isAlive = true;
		MAXHP = 800;
		ATK = 50;
		MANUVER = 1;
		RANGE = 1.1f;
		HP = MAXHP;
		static Texture texture1; //一样必须设置成静态，原因和font一样
		texture1.loadFromFile("Textures/warrior/warrior.png");
		sprite.setTexture(texture1);
		sprite.setPosition(x * 80 -80, y * 80 + 40.0f);
		float scaleX = 80.0f / 128.0f;  // 目标宽度 / 原始宽度
		float scaleY = 80.0f / 128.0f;  // 目标高度 / 原始高度
		sprite.setScale(scaleX, scaleY);
	}

	if (typenum == 2) { //mage
		isAlive = true;
		MAXHP = 500;
		ATK = 80;
		MANUVER = 1;
		RANGE = 2.1f;
		HP = MAXHP;
		static Texture texture2; 
		texture2.loadFromFile("Textures/mage/mage.png");
		sprite.setTexture(texture2);
		sprite.setPosition(x * 80-80, y * 80 + 40.0f);
		float scaleX = 80.0f / 128.0f;  // 目标宽度 / 原始宽度
		float scaleY = 80.0f / 128.0f;  // 目标高度 / 原始高度
		sprite.setScale(scaleX, scaleY);
	}

	if (typenum == 3) { //killer
		isAlive = true;
		MAXHP = 700;
		ATK = 100;
		MANUVER = 2;
		RANGE = 1.1f;
		HP = MAXHP;
		static Texture texture3; 
		texture3.loadFromFile("Textures/killer/killer.png");
		sprite.setTexture(texture3);
		sprite.setPosition(x * 80-80, y * 80 + 40.0f);
		float scaleX = 80.0f / 128.0f;  // 目标宽度 / 原始宽度
		float scaleY = 80.0f / 128.0f;  // 目标高度 / 原始高度
		sprite.setScale(scaleX, scaleY);
	}

	if (typenum == 4) { //warrior upgrade
		isAlive = true;
		MAXHP = 1200;
		ATK = 70;
		MANUVER = 1;
		RANGE = 1.1f;
		HP = MAXHP;
		static Texture texture4;
		texture4.loadFromFile("Textures/warrior/warrior.png");
		sprite.setTexture(texture4);
		sprite.setPosition(x * 80 - 80, y * 80 + 40.0f);
		float scaleX = 80.0f / 128.0f;  // 目标宽度 / 原始宽度
		float scaleY = 80.0f / 128.0f;  // 目标高度 / 原始高度
		sprite.setScale(scaleX, scaleY);
	}

	if (typenum == 5) { //mage upgrade
		isAlive = true;
		MAXHP = 800;
		ATK = 120;
		MANUVER = 1;
		RANGE = 2.1f;
		HP = MAXHP;
		static Texture texture5;
		texture5.loadFromFile("Textures/mage/mage.png");
		sprite.setTexture(texture5);
		sprite.setPosition(x * 80 - 80, y * 80 + 40.0f);
		float scaleX = 80.0f / 128.0f;  // 目标宽度 / 原始宽度
		float scaleY = 80.0f / 128.0f;  // 目标高度 / 原始高度
		sprite.setScale(scaleX, scaleY);
	}

	if (typenum == 6) { //killer upgrade
		isAlive = true;
		MAXHP = 900;
		ATK = 150;
		MANUVER = 2;
		RANGE = 1.1f;
		HP = MAXHP;
		static Texture texture6;
		texture6.loadFromFile("Textures/killer/killer.png");
		sprite.setTexture(texture6);
		sprite.setPosition(x * 80 - 80, y * 80 + 40.0f);
		float scaleX = 80.0f / 128.0f;  // 目标宽度 / 原始宽度
		float scaleY = 80.0f / 128.0f;  // 目标高度 / 原始高度
		sprite.setScale(scaleX, scaleY);
	}
}

void Soldier::setPosition(const Vector2i& MousPos) {
	this->x = (int)(MousPos.x / 80) + 1;
	this->y = (int)((MousPos.y - 120.0) / 80) + 1;
	sprite.setPosition(x * 80 - 80.0f, y * 80 + 40.0f);
}

void Soldier::Move(int MoveX, int MoveY) {
	if (abs(MoveX) + abs(MoveY) > MANUVER) {
		std::cout << "Move Error! MoveX: " << MoveX << ", MoveY: " << MoveY << "\n";
		return;
	}
	x += MoveX;
	y += MoveY;
	sprite.setPosition(x * 80 - 80.0f, y * 80 + 40.0f);
}

float Soldier::GetDistance(Soldier* target) {
	if (target == nullptr) {
		std::cout << "WARNING: GetDistance Error! Target is null.\n";
		return -1;
	}
	float distance = sqrt(pow(target->x - this->x, 2) + 
		pow(target->y - this->y, 2));
	std::cout << "Distance to enemy: " << distance << std::endl;
	return distance;
}

void Soldier::Attack(Soldier* target) {
	std::cout << "Attack!" << std::endl;
	if (!isAlive) return;
	if (!target->isAlive) {
		std::cout << "Attack Error! Target is dead.\n";
		return;
	}
	if (target == nullptr) {
		std::cout << "Attack Error! Target is null.\n";
		return;
	}
	if (GetDistance(target) > RANGE) {
		std::cout << "Attack Error! Target out of range.\n";
		return;
	}
	target->HP -= ATK;
	if (target->HP <= 0) {
		target->isAlive = false; //删除杀死的目标士兵
	}
}

void Soldier::render(RenderWindow& window) {
	if (!isAlive) return;

	sf::Vector2f scale = sprite.getScale();
	float absScaleX = std::abs(scale.x);
	float scaleY = scale.y;

	// 己方士兵水平翻转，敌方正常
	if (side == true) {
		sprite.setScale(-absScaleX, scaleY);
		// 由于翻转后锚点在右上角，需要调整位置
		sf::FloatRect bounds = sprite.getGlobalBounds();
		sprite.setPosition(sprite.getPosition().x + bounds.width, sprite.getPosition().y);
	}
	else {
		sprite.setScale(absScaleX, scaleY);
	}

	window.draw(sprite);

	// 渲染后恢复sprite位置，避免多次叠加
	if (side == true) {
		sf::FloatRect bounds = sprite.getGlobalBounds();
		sprite.setPosition(sprite.getPosition().x - bounds.width, sprite.getPosition().y);
	}

	// 绘制血条
    //血条大小和位置
	float barWidth = 60.0f;
	float barHeight = 8.0f;
	float barOffsetY = -15.0f;

	float hpPercent = static_cast<float>(HP) / static_cast<float>(MAXHP);
	if (hpPercent < 0) hpPercent = 0;
	if (hpPercent > 1) hpPercent = 1;
	//绘制矩形
	RectangleShape backBar(Vector2f(barWidth, barHeight));
	backBar.setFillColor(Color(50, 50, 50));
	backBar.setPosition(sprite.getPosition().x + (sprite.getGlobalBounds().width - barWidth) / 2,
		sprite.getPosition().y + barOffsetY);

	RectangleShape hpBar(Vector2f(barWidth * hpPercent, barHeight));
	if (side==true){ 
		hpBar.setFillColor(Color::Green); 
	}
	else {
		hpBar.setFillColor(Color::Red);
	}
	
	hpBar.setPosition(backBar.getPosition());

	window.draw(backBar);
	window.draw(hpBar);
}


int getSteps(Soldier* soldier1, Soldier* soldier2) {
	return abs(soldier1->x - soldier2->x) + abs(soldier1->y - soldier2->y);
}

int Soldier::getSoldierAtPosition(Soldier** AllSoldiers, int SoldierCount, int x, int y) {
	for (int i = 0; i < SoldierCount; i++) {
		if (AllSoldiers[i]->isAlive && AllSoldiers[i]->x == x && AllSoldiers[i]->y == y) {
			return i;
		}
	}
	return -1; // 未找到符合要求的士兵
}



bool Soldier::initializeAI(const std::string& model_path) {
	bool success = ai.loadModel(model_path);
	if (success) {
		AI_initialized = true;
	}
	else {
		std::cout << "Failed to initialize AI!" << std::endl;
	}
	return success;
}

//设置AI使用CPU或CUDA
void Soldier::setAIDevice(const std::string& device_type) {
	if (!AI_initialized) {
		std::cout << "AI not initialized yet!" << std::endl;
		return;
	}
	ai.setDevice(device_type);
	return;
}



void Soldier::battleAI(Soldier** AllSoldiers, int SoldierCount, int selfCount, int turnCount) {
	std::cout << "Soldier " << selfCount << " BattleAI operating!\n";
	if (!this->isAlive) return;

	std::vector<float> state = gameState(AllSoldiers, SoldierCount, selfCount, turnCount);
	std::vector<int> actions = getValidActions(AllSoldiers, SoldierCount, selfCount);

	if (actions.empty()) {
		std::cout << "无有效动作可选择" << std::endl;
		return;
	}
	int choice = ai.makeDecision(state, actions);
	std::cout << "AI选择动作: " << choice << std::endl;
	Soldier::actionInterpreter(choice,AllSoldiers,SoldierCount,selfCount);
}

const std::vector<std::pair<int, int>> ACTION_OFFSETS = {
	// 距离1的8个方向 (actions 0-7)
	{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1},
	// 距离2的4个主要方向 (actions 8-11) 
	{-2, 0}, {2, 0}, {0, -2}, {0, 2}
};

void Soldier::actionInterpreter(int action, Soldier** AllSoldiers, int SoldierCount, int selfCount) {
	std::cout << "Soldier " << selfCount << " actionInterpreter operating! Action: " << action << std::endl;

	if (!this->isAlive) {
		std::cout << "士兵已死亡，无法执行动作" << std::endl;
		return;
	}

	// 新的动作编码：
	// 0-11:  移动动作 (使用相对位移)
	// 12-23: 攻击动作 (使用相对位移)

	if (action >= 0 && action <= 11) {
		// 移动动作
		int dr = ACTION_OFFSETS[action].first;   // y方向位移
		int dc = ACTION_OFFSETS[action].second;  // x方向位移

		int target_x = this->x + dc;
		int target_y = this->y + dr;

		std::cout << "执行移动: 从(" << this->x << "," << this->y << ") 到 ("
			<< target_x << "," << target_y << ")" << std::endl;

		// 验证移动的有效性
		if (target_x >= 1 && target_x <= 10 && target_y >= 1 && target_y <= 6) {
			// 检查目标位置是否被占用
			bool occupied = false;
			for (int i = 0; i < SoldierCount; ++i) {
				if (i != selfCount && AllSoldiers[i]->isAlive &&
					AllSoldiers[i]->x == target_x && AllSoldiers[i]->y == target_y) {
					occupied = true;
					break;
				}
			}

			if (!occupied && abs(dr) + abs(dc) <= this->MANUVER) {
				this->Move(dc, dr);  // Move函数参数是 (x_offset, y_offset)
				std::cout << "移动成功" << std::endl;
			}
			else {
				std::cout << "移动失败：位置被占用或超出移动范围" << std::endl;
			}
		}
		else {
			std::cout << "移动失败：超出棋盘边界" << std::endl;
		}
	}
	else if (action >= 12 && action <= 23) {
		// 攻击动作
		int offset_idx = action - 12;
		int dr = ACTION_OFFSETS[offset_idx].first;   // y方向位移
		int dc = ACTION_OFFSETS[offset_idx].second;  // x方向位移

		int target_x = this->x + dc;
		int target_y = this->y + dr;

		std::cout << "尝试攻击位置: (" << target_x << "," << target_y << ")" << std::endl;

		// 验证攻击的有效性
		if (target_x >= 1 && target_x <= 10 && target_y >= 1 && target_y <= 6) {
			// 查找目标位置的敌人
			Soldier* target = nullptr;
			for (int i = 0; i < SoldierCount; ++i) {
				if (AllSoldiers[i]->isAlive &&
					AllSoldiers[i]->x == target_x && AllSoldiers[i]->y == target_y &&
					AllSoldiers[i]->side != this->side) {
					target = AllSoldiers[i];
					break;
				}
			}

			if (target) {
				// 检查攻击距离
				float distance = sqrt(dr * dr + dc * dc);
				if (distance <= this->RANGE) {
					std::cout << "攻击目标士兵，造成 " << this->ATK << " 点伤害" << std::endl;
					this->Attack(target);
				}
				else {
					std::cout << "攻击失败：目标超出攻击范围" << std::endl;
				}
			}
			else {
				std::cout << "攻击失败：目标位置没有敌人" << std::endl;
			}
		}
		else {
			std::cout << "攻击失败：目标位置超出棋盘边界" << std::endl;
		}
	}
	else {
		std::cout << "动作编码错误：" << action << " 不在有效范围内 (0-23)" << std::endl;
	}
}










	//在这里调用模型，注意数据之间的转换
	// AllSoldiers是一个指针数组，其中每个成员是士兵的指针，士兵的side,HP,ATK都可以
	// 直接访问。

	/* 这是原有的AI策略

	std::cout << selfCount << ": is Alive. \n";
	// 1. 优先攻击射程内的敌人
	for (int i = 0; i < SoldierCount; i++) {
		if (i == selfCount) continue;
		Soldier* enemy = AllSoldiers[i];
		if (enemy->isAlive && enemy->side != this->side) {
			if (getSteps(this,enemy) <= RANGE) {
				Attack(enemy);
				return; // 攻击后直接结束本回合
			}
		}
	}

	// 2. 没有可攻击目标时，寻找最近的敌人
	int nearestIdx = -1;
	int minDistance = 10;
	for (int i = 0; i < SoldierCount; i++) {
		if (i == selfCount) continue;
		Soldier* enemy = AllSoldiers[i];
		std::cout << enemy->side << " " << enemy->isAlive << std::endl;
		if (enemy->isAlive && enemy->side != this->side) {
			int dist = getSteps(this,enemy);
			if (dist < minDistance) {
				minDistance = dist;
				nearestIdx = i;
			}
		}
	}
	std::cout << selfCount << ": the nearest enemy is " << nearestIdx<<std::endl;

	// 3. 向最近的敌人靠近
	if (nearestIdx != -1) {
		Soldier* target = AllSoldiers[nearestIdx];
		int dx = target->x - this->x;
		int dy = target->y - this->y;
		int stepX = 0, stepY = 0;
		// 优先横向或纵向移动
		stepX = (dx > 0) ? 1 : (dx < 0 ? -1 : 0);
		stepY = 0;
		// 检查目标格是否被占用
		int newX = this->x + stepX;
		int newY = this->y + stepY;
		bool blocked = false;
		for (int i = 0; i < SoldierCount; ++i) {
			if (i == selfCount) continue;
			if (AllSoldiers[i]->isAlive && AllSoldiers[i]->x == newX && AllSoldiers[i]->y == newY) {
				blocked = true;
				break;
			}
		}
		if (!blocked) {
			Move(stepX, stepY);
		}
		else {
			stepY = (dy > 0) ? 1 : (dy < 0 ? -1 : 0);
			stepX = 0;
			newX = this->x + stepX;
			newY = this->y + stepY;
			blocked = false;
			for (int i = 0; i < SoldierCount; ++i) {
				if (i == selfCount) continue;
				if (AllSoldiers[i]->isAlive && AllSoldiers[i]->x == newX && AllSoldiers[i]->y == newY) {
					blocked = true;
					break;
				}
			}
			if (!blocked) {
				Move(stepX, stepY);
			}
			else {
				std::cout << selfCount << ": No way to approach the enemy.\n";
			}
		}
	}*/


