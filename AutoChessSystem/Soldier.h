#ifndef SOLDIER_H
#define SOLDIER_H

#include "AI_model.h"
#include <SFML/Graphics.hpp>
#include <torch/torch.h>
using namespace sf;

class Soldier {
public:
	int type; //士兵类型，1= Warrior, 2 = Mage, 3 = Killer,

	void battleAI(Soldier** AllSoldiers, int SoldierCount, int selfCount, int turnCount); //战斗AI

	bool isAlive; //士兵是否存活，这是一切逻辑的基础
	const bool side; //士兵所属阵营，1表示玩家阵营，0表示敌人阵营

	int HP;
	int ATK;
	int MANUVER; //移动力
	float RANGE; //攻击范围
	int MAXHP; //最大生命值，注意与HP的区别

	int x;
	int y; //位置坐标，注意这表示棋盘网格上的位置，而不是像素位置

	void setPosition(const Vector2i& MousPos);

	Sprite sprite;

	Soldier(bool side, int typenum,const Vector2f& position); //会根据鼠标在棋盘上的点击位置来设置士兵的初始位置
	Soldier() = default; //默认构造函数

	void Move(int MoveX, int MoveY); //MoveX和MoveY表示相对于当前位置的偏移量，同样基于棋盘坐标

	float GetDistance(Soldier* target); //获取与目标士兵的距离，取xy坐标的平方和开根
	static int getSoldierAtPosition(Soldier** AllSoldiers,int SoldierCount, int x, int y);//返回（x，y）处的目标编号

	void Attack(Soldier* target); //攻击目标士兵

	void render(RenderWindow& window); //渲染士兵

	static AI_model ai;
	static bool initializeAI(const std::string& model_path);
	static void setAIDevice(const std::string& device_type);
	void actionInterpreter(int action,Soldier** AllSoldiers,int SoldierCount,int selfCount);

	static bool AI_initialized;
};


#endif
