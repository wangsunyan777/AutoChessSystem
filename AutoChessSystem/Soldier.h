#ifndef SOLDIER_H
#define SOLDIER_H

#include "AI_model.h"
#include <SFML/Graphics.hpp>
#include <torch/torch.h>
using namespace sf;

class Soldier {
public:
	int type; //ʿ�����ͣ�1= Warrior, 2 = Mage, 3 = Killer,

	void battleAI(Soldier** AllSoldiers, int SoldierCount, int selfCount, int turnCount); //ս��AI

	bool isAlive; //ʿ���Ƿ������һ���߼��Ļ���
	const bool side; //ʿ��������Ӫ��1��ʾ�����Ӫ��0��ʾ������Ӫ

	int HP;
	int ATK;
	int MANUVER; //�ƶ���
	float RANGE; //������Χ
	int MAXHP; //�������ֵ��ע����HP������

	int x;
	int y; //λ�����꣬ע�����ʾ���������ϵ�λ�ã�����������λ��

	void setPosition(const Vector2i& MousPos);

	Sprite sprite;

	Soldier(bool side, int typenum,const Vector2f& position); //���������������ϵĵ��λ��������ʿ���ĳ�ʼλ��
	Soldier() = default; //Ĭ�Ϲ��캯��

	void Move(int MoveX, int MoveY); //MoveX��MoveY��ʾ����ڵ�ǰλ�õ�ƫ������ͬ��������������

	float GetDistance(Soldier* target); //��ȡ��Ŀ��ʿ���ľ��룬ȡxy�����ƽ���Ϳ���
	static int getSoldierAtPosition(Soldier** AllSoldiers,int SoldierCount, int x, int y);//���أ�x��y������Ŀ����

	void Attack(Soldier* target); //����Ŀ��ʿ��

	void render(RenderWindow& window); //��Ⱦʿ��

	static AI_model ai;
	static bool initializeAI(const std::string& model_path);
	static void setAIDevice(const std::string& device_type);
	void actionInterpreter(int action,Soldier** AllSoldiers,int SoldierCount,int selfCount);

	static bool AI_initialized;
};


#endif
