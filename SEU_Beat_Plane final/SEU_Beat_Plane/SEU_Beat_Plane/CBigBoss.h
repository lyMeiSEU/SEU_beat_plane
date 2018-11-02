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

	int CBB_nCountFire; //控制发射子弹类型
	int CBB_nMoveF; //BOSS移动方向
	int CBB_nBulletNumber; //控制转圈所发出的子弹个数
	float CBB_fStayTime; //发射激光时停止移动时间
};
