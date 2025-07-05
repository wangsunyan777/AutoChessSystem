//��Ϸ״̬��AI�ӿ�ת��
#pragma once

#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "Soldier.h"

/*
 * ����Ϸ״̬����ΪAI��Ҫ��612ά����
 *
 * @param AllSoldiers ����ʿ��������
 * @param SoldierCount ʿ������
 * @param selfCount ��ǰ�ж�ʿ��������
 * @param turnCount ��ǰ�غ���
 * @return 612ά��״̬����
 */

std::vector<float> gameState(Soldier** AllSoldiers, int SoldierCount, int selfCount, int turnCount);
std::vector<int> getValidActions(Soldier** AllSoldiers, int SoldierCount, int selfCount);
