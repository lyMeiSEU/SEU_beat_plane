#pragma once
#include "stdafx.h"
#include "CEnemyPlane.h"

class BigBoss :public EnemyPlane
{
public:
	BigBoss();
	void Update();
	void CircleBullet(int x, int y, BulletType bulletType);
	void BarBullet(int x, int y, BulletType bulletType);
	static int bossstatus;
private:

	int CBB_nCountFire; //���Ʒ����ӵ�����
	int CBB_nMoveF; //BOSS�ƶ�����
	int CBB_nBulletNumber; //����תȦ���������ӵ�����
	float CBB_fStayTime; //���伤��ʱֹͣ�ƶ�ʱ��
};
