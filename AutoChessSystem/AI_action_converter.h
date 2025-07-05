//游戏状态与AI接口转换
#pragma once

#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "Soldier.h"

/*
 * 将游戏状态编码为AI需要的612维向量
 *
 * @param AllSoldiers 所有士兵的数组
 * @param SoldierCount 士兵总数
 * @param selfCount 当前行动士兵的索引
 * @param turnCount 当前回合数
 * @return 612维的状态向量
 */

std::vector<float> gameState(Soldier** AllSoldiers, int SoldierCount, int selfCount, int turnCount);
std::vector<int> getValidActions(Soldier** AllSoldiers, int SoldierCount, int selfCount);
